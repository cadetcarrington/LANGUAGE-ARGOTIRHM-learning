#include <cstring>
#include <iostream>
#include <string>
#include <sys/time.h>
#include <vector>

#include "../include/dgemm_optimized.h"
#include "../include/file_operations.h"
#include "../include/matrix_operations.h"

namespace {

void addMatrix(double* A, const double* B, int M) {
    for (int i = 0; i < M * M; ++i) {
        A[i] += B[i];
    }
}

bool parseSize(int argc, const char* argv[], int& M, int& N) {
    M = 1024;
    N = 4096;
    if (argc == 1 || std::strcmp(argv[1], "1024") == 0) {
        std::cout << "RUNNING SIMD DGEMM: M = 1024" << std::endl;
        return true;
    }
    if (argc == 2 && std::strcmp(argv[1], "4096") == 0) {
        M = 4096;
        N = 4096;
        std::cout << "RUNNING SIMD DGEMM: M = 4096" << std::endl;
        return true;
    }
    std::cout << "Usage: " << argv[0] << " [1024|4096]" << std::endl;
    return false;
}

}  // namespace

int main(int argc, const char* argv[]) {
    int M = 0;
    int N = 0;
    if (!parseSize(argc, argv, M, N)) {
        return 1;
    }

    std::vector<double> A(static_cast<size_t>(M) * N);
    std::vector<double> B(static_cast<size_t>(N) * M);
    std::vector<double> C(static_cast<size_t>(M) * M);
    std::vector<double> res(static_cast<size_t>(M) * M);
    matrixInit(A.data(), B.data(), C.data(), M, N);

    timeval start;
    timeval end;
    gettimeofday(&start, nullptr);
    dgemmSimdBlocked(A.data(), B.data(), res.data(), M, N);
    addMatrix(res.data(), C.data(), M);
    gettimeofday(&end, nullptr);

    const double ms = (end.tv_sec - start.tv_sec) * 1000.0 +
                      (end.tv_usec - start.tv_usec) / 1000.0;
    std::printf("Using time : %f ms\n", ms);

    writeMatrixToFile(res.data(), M, "result.txt");
    const std::string ref = "./data/refer_" + std::to_string(M) + ".txt";
    compareFiles(ref.c_str(), "result.txt");
    return 0;
}
