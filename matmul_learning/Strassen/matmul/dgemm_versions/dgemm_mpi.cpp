#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <mpi.h>

#include "../include/dgemm_optimized.h"
#include "../include/file_operations.h"
#include "../include/matrix_operations.h"

namespace {

bool parseSize(int argc, char** argv, int rank, int& M, int& N) {
    M = 1024;
    N = 4096;
    if (argc == 1 || std::strcmp(argv[1], "1024") == 0) {
        if (rank == 0) {
            std::cout << "RUNNING MPI DGEMM: M = 1024" << std::endl;
        }
        return true;
    }
    if (argc == 2 && std::strcmp(argv[1], "4096") == 0) {
        M = 4096;
        N = 4096;
        if (rank == 0) {
            std::cout << "RUNNING MPI DGEMM: M = 4096" << std::endl;
        }
        return true;
    }
    if (rank == 0) {
        std::cout << "Usage: " << argv[0] << " [1024|4096]" << std::endl;
    }
    return false;
}

void buildCounts(int M, int width, int size,
                 std::vector<int>& counts, std::vector<int>& displs) {
    counts.resize(size);
    displs.resize(size);
    int offset = 0;
    const int baseRows = M / size;
    const int extra = M % size;
    for (int r = 0; r < size; ++r) {
        const int rows = baseRows + (r < extra ? 1 : 0);
        counts[r] = rows * width;
        displs[r] = offset;
        offset += counts[r];
    }
}

void addMatrix(double* A, const double* B, int count) {
    for (int i = 0; i < count; ++i) {
        A[i] += B[i];
    }
}

}  // namespace

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank = 0;
    int size = 1;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int M = 0;
    int N = 0;
    if (!parseSize(argc, argv, rank, M, N)) {
        MPI_Finalize();
        return 1;
    }

    std::vector<double> A;
    std::vector<double> B(static_cast<size_t>(N) * M);
    std::vector<double> C;
    std::vector<double> res;
    if (rank == 0) {
        A.resize(static_cast<size_t>(M) * N);
        C.resize(static_cast<size_t>(M) * M);
        res.resize(static_cast<size_t>(M) * M);
        matrixInit(A.data(), B.data(), C.data(), M, N);
    }

    std::vector<int> aCounts;
    std::vector<int> aDispls;
    std::vector<int> cCounts;
    std::vector<int> cDispls;
    buildCounts(M, N, size, aCounts, aDispls);
    buildCounts(M, M, size, cCounts, cDispls);

    const int localRows = aCounts[rank] / N;
    std::vector<double> localA(static_cast<size_t>(aCounts[rank]));
    std::vector<double> localC(static_cast<size_t>(cCounts[rank]));
    std::vector<double> localRes(static_cast<size_t>(cCounts[rank]));

    MPI_Bcast(B.data(), static_cast<int>(B.size()), MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatterv(rank == 0 ? A.data() : nullptr, aCounts.data(), aDispls.data(),
                 MPI_DOUBLE, localA.data(), aCounts[rank], MPI_DOUBLE, 0,
                 MPI_COMM_WORLD);
    MPI_Scatterv(rank == 0 ? C.data() : nullptr, cCounts.data(), cDispls.data(),
                 MPI_DOUBLE, localC.data(), cCounts[rank], MPI_DOUBLE, 0,
                 MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    const double start = MPI_Wtime();
    dgemmRowsSimdBlocked(localA.data(), B.data(), localRes.data(),
                         localRows, M, N);
    addMatrix(localRes.data(), localC.data(), cCounts[rank]);
    MPI_Barrier(MPI_COMM_WORLD);
    const double elapsedMs = (MPI_Wtime() - start) * 1000.0;

    double maxElapsedMs = 0.0;
    MPI_Reduce(&elapsedMs, &maxElapsedMs, 1, MPI_DOUBLE, MPI_MAX, 0,
               MPI_COMM_WORLD);

    MPI_Gatherv(localRes.data(), cCounts[rank], MPI_DOUBLE,
                rank == 0 ? res.data() : nullptr, cCounts.data(), cDispls.data(),
                MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::printf("Using time : %f ms\n", maxElapsedMs);
        writeMatrixToFile(res.data(), M, "result.txt");
        const std::string ref = "./data/refer_" + std::to_string(M) + ".txt";
        compareFiles(ref.c_str(), "result.txt");
    }

    MPI_Finalize();
    return 0;
}
