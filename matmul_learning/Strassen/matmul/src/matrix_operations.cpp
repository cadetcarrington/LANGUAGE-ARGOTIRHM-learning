#include <random>

#include "dgemm_optimized.h"
#include "matrix_operations.h"

using namespace std;


void matrixInit(double* A, double* B, double* C, int M, int N){
    default_random_engine eng(30);
    uniform_real_distribution<double> distr(MIN,MAX);
    for(int i = 0; i < M * N ; ++ i){
        A[i] = distr(eng);
    }
    for(int i = 0; i < M * N ; ++ i){
        B[i] = distr(eng);
    }
    for(int i = 0; i < M *M; ++ i){
        C[i] = distr(eng);
    }
}

void matrixMultiplication(double* A, double* B, double* res, int M, int N) {
    dgemmOpenMpBlocked(A, B, res, M, N);
}

void matrixSelfAddition(double* A, double* B, int M, int N) {
    (void)N;
#if defined(_OPENMP)
#pragma omp parallel for schedule(static)
#endif
    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < M; ++j) {
            A[i * M + j] += B[i * M + j];
        }
    }
}
