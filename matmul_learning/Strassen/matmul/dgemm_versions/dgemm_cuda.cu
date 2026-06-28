#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include <cuda_runtime.h>

namespace {

constexpr int MIN_VALUE = 1;
constexpr int MAX_VALUE = 50;
constexpr int TILE = 16;

#define CUDA_CHECK(call)                                                     \
    do {                                                                     \
        cudaError_t err__ = (call);                                           \
        if (err__ != cudaSuccess) {                                           \
            std::fprintf(stderr, "CUDA error %s:%d: %s\n", __FILE__,         \
                         __LINE__, cudaGetErrorString(err__));               \
            std::exit(EXIT_FAILURE);                                          \
        }                                                                    \
    } while (0)

__global__ void dgemmTiledAddKernel(const double* __restrict__ A,
                                    const double* __restrict__ B,
                                    const double* __restrict__ C,
                                    double* __restrict__ res,
                                    int M, int N) {
    __shared__ double As[TILE][TILE];
    __shared__ double Bs[TILE][TILE];

    const int row = blockIdx.y * TILE + threadIdx.y;
    const int col = blockIdx.x * TILE + threadIdx.x;
    double sum = 0.0;

    for (int kk = 0; kk < N; kk += TILE) {
        const int aCol = kk + threadIdx.x;
        const int bRow = kk + threadIdx.y;
        As[threadIdx.y][threadIdx.x] =
            (row < M && aCol < N) ? A[row * N + aCol] : 0.0;
        Bs[threadIdx.y][threadIdx.x] =
            (bRow < N && col < M) ? B[bRow * M + col] : 0.0;
        __syncthreads();

#pragma unroll
        for (int k = 0; k < TILE; ++k) {
            sum += As[threadIdx.y][k] * Bs[k][threadIdx.x];
        }
        __syncthreads();
    }

    if (row < M && col < M) {
        res[row * M + col] = sum + C[row * M + col];
    }
}

void matrixInit(double* A, double* B, double* C, int M, int N) {
    std::default_random_engine eng(30);
    std::uniform_real_distribution<double> distr(MIN_VALUE, MAX_VALUE);
    for (int i = 0; i < M * N; ++i) {
        A[i] = distr(eng);
    }
    for (int i = 0; i < M * N; ++i) {
        B[i] = distr(eng);
    }
    for (int i = 0; i < M * M; ++i) {
        C[i] = distr(eng);
    }
}

void writeMatrixToFile(const double* matrix, int size, const char* filename) {
    FILE* out = std::fopen(filename, "w");
    if (out == nullptr) {
        std::printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::fprintf(out, "%.2lf\t", matrix[i * size + j]);
        }
        std::fprintf(out, "\n");
    }
    std::fclose(out);
}

void compareFiles(const char* standardFile, const char* resultFile) {
    FILE* standard = std::fopen(standardFile, "r");
    FILE* result = std::fopen(resultFile, "r");
    if (!standard || !result) {
        std::cerr << "Error opening file(s)" << std::endl;
        if (standard) {
            std::fclose(standard);
        }
        if (result) {
            std::fclose(result);
        }
        return;
    }

    double num1 = 0.0;
    double num2 = 0.0;
    bool isCorrect = true;
    while (std::fscanf(standard, "%lf", &num1) != EOF &&
           std::fscanf(result, "%lf", &num2) != EOF) {
        if (std::fabs(num1 - num2) > 1.0) {
            isCorrect = false;
            break;
        }
    }

    if (isCorrect) {
        std::cout << "\033[1;32mThe result is correct!\033[0m" << std::endl;
    } else {
        std::cout << "\033[1;31mThe result is wrong!\033[0m" << std::endl;
    }
    std::fclose(standard);
    std::fclose(result);
}

bool parseSize(int argc, char** argv, int& M, int& N) {
    M = 1024;
    N = 4096;
    if (argc == 1 || std::strcmp(argv[1], "1024") == 0) {
        std::cout << "RUNNING CUDA DGEMM: M = 1024" << std::endl;
        return true;
    }
    if (argc == 2 && std::strcmp(argv[1], "4096") == 0) {
        M = 4096;
        N = 4096;
        std::cout << "RUNNING CUDA DGEMM: M = 4096" << std::endl;
        return true;
    }
    std::cout << "Usage: " << argv[0] << " [1024|4096]" << std::endl;
    return false;
}

}  // namespace

int main(int argc, char** argv) {
    int M = 0;
    int N = 0;
    if (!parseSize(argc, argv, M, N)) {
        return 1;
    }

    const size_t bytesA = static_cast<size_t>(M) * N * sizeof(double);
    const size_t bytesB = static_cast<size_t>(N) * M * sizeof(double);
    const size_t bytesC = static_cast<size_t>(M) * M * sizeof(double);

    std::vector<double> A(static_cast<size_t>(M) * N);
    std::vector<double> B(static_cast<size_t>(N) * M);
    std::vector<double> C(static_cast<size_t>(M) * M);
    std::vector<double> res(static_cast<size_t>(M) * M);
    matrixInit(A.data(), B.data(), C.data(), M, N);

    double* dA = nullptr;
    double* dB = nullptr;
    double* dC = nullptr;
    double* dRes = nullptr;
    CUDA_CHECK(cudaMalloc(&dA, bytesA));
    CUDA_CHECK(cudaMalloc(&dB, bytesB));
    CUDA_CHECK(cudaMalloc(&dC, bytesC));
    CUDA_CHECK(cudaMalloc(&dRes, bytesC));

    cudaEvent_t start;
    cudaEvent_t stop;
    CUDA_CHECK(cudaEventCreate(&start));
    CUDA_CHECK(cudaEventCreate(&stop));
    CUDA_CHECK(cudaEventRecord(start));

    CUDA_CHECK(cudaMemcpy(dA, A.data(), bytesA, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(dB, B.data(), bytesB, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(dC, C.data(), bytesC, cudaMemcpyHostToDevice));

    const dim3 block(TILE, TILE);
    const dim3 grid((M + TILE - 1) / TILE, (M + TILE - 1) / TILE);
    dgemmTiledAddKernel<<<grid, block>>>(dA, dB, dC, dRes, M, N);
    CUDA_CHECK(cudaGetLastError());

    CUDA_CHECK(cudaMemcpy(res.data(), dRes, bytesC, cudaMemcpyDeviceToHost));
    CUDA_CHECK(cudaEventRecord(stop));
    CUDA_CHECK(cudaEventSynchronize(stop));

    float ms = 0.0f;
    CUDA_CHECK(cudaEventElapsedTime(&ms, start, stop));
    std::printf("Using time : %f ms\n", static_cast<double>(ms));

    writeMatrixToFile(res.data(), M, "result.txt");
    const std::string ref = "./data/refer_" + std::to_string(M) + ".txt";
    compareFiles(ref.c_str(), "result.txt");

    CUDA_CHECK(cudaEventDestroy(start));
    CUDA_CHECK(cudaEventDestroy(stop));
    CUDA_CHECK(cudaFree(dA));
    CUDA_CHECK(cudaFree(dB));
    CUDA_CHECK(cudaFree(dC));
    CUDA_CHECK(cudaFree(dRes));
    return 0;
}
