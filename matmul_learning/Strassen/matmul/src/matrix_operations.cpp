#include <random>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <algorithm>

#include "matrix_operations.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////
///                           !!!此函数不允许修改!!!                                ///
////////////////////////////////////////////////////////////////////////////////////
//↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ //
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
//↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ //
////////////////////////////////////////////////////////////////////////////////////
///                           !!!此函数不允许修改!!!                                ///
////////////////////////////////////////////////////////////////////////////////////

void matrixadd(double * A, double * B, double * res, int la, int lb, int lc, int N){
    for (int i = 0; i < N; i ++){
        for(int j = 0; j < N; j ++){
            res[i * lc + j] = A[i * la + j] + B[i * lb + j]; 
        }
    }
}

void matrixsub(double * A, double * B, double * res, int la, int lb, int lc, int N){
    for (int i = 0; i < N; i ++){
        for (int j = 0; j < N; j ++){
            res[i * lc + j] = A[i * la + j] - B[i * lb + j];
        }
    }
}

void Strassenmatrix(double* A, double* B, double* res, int la, int lb, int lc, int N){
    int k = N / 2;
    int k2 = k * k;

    vector<double> T1(k2);  vector<double> P3(k2);
    vector<double> T2(k2);  vector<double> P4(k2);
    vector<double> P1(k2);  vector<double> P5(k2);
    vector<double> P2(k2);  vector<double> P6(k2);
    vector<double> P7(k2);

    double * A11 = A, * A12 = A + k, * A21 = A + k * la;
    double * A22 = A + k * la + k;

    double * B11 = B, * B12 = B + k;
    double * B21 = B + k * lb, * B22 = B + k * lb + k;

    matrixsub(B12, B22, T1.data(),lb, lb, k, k);
    Strassenmatrix(A11, T1.data(), P1.data(), la, k, k, k);

    matrixadd(A11, A12, T1.data(), la, la, k, k);
    Strassenmatrix(T1.data(), B22, P2.data(), k, lb, k, k);

    matrixadd(A21, A22, T1.data(), la, la, k, k);
    Strassenmatrix(T1.data(), B11, P3.data(), k, lb, k, k);

    matrixsub(B21, B11, T1.data(), lb, lb, k, k);
    Strassenmatrix(A22, T1.data(), P4.data(), la, k, k, k);

    matrixadd(A11, A22, T1.data(), la, la, k, k);
    matrixadd(B11, B22, T2.data(), lb, lb, k, k);
    Strassenmatrix(T1.data(), T2.data(), P5.data(), k, k, k, k);

    matrixsub(A11, A22, T1.data(), la, la, k, k);
    matrixsub(B21, B22, T2.data(), lb, lb, k, k);
    Strassenmatrix(T1.data(), T2.data(), P6.data(), k, k, k, k);

    matrixsub(A11, A21, T1.data(), la, la, k, k);
    matrixadd(B11, B12, T2.data(), lb, lb, k, k);
    Strassenmatrix(T1.data(), T2.data(), P7.data(), k, k, k, k);

    double * C11 = res;
    double * C12 = res + k;
    double * C21 = res + k * lc;
    double * C22 = res + k * lc + k;

    for (int i = 0; i < k; i ++){
        for (int j = 0; j < k; j ++){
            C11[j] = P5[i * k + j] + P4[i * k + j] - P2[i * k + j] +P6[i * k + j];
            C12[j] = P1[i * k + j] + P2[i * k + j];
            C21[j] = P3[i * k + j] + P4[i * k + j];
            C22[j] = P1[i * k + j] + P5[i * k + j] - P3[i * k + j] - P7[i * k + j];
        }
    }
}

void matrixMultiplication(double* A, double* B, double* res, int M, int N) {
    // for(int i = 0; i < M; ++ i){
    //     for(int j = 0; j < M; ++ j){
    //         double t = 0.0;
    //         for(int k = 0;  k < N; ++ k){
    //             t += A[i * N + k] * B[k * M + j];
    //         }
    //         res[i * M + j] = t;
    //     }
    // }

    int bs = 512;

    int mp = ((M + bs - 1) / bs) * bs;
    int np = ((N + bs - 1) / bs) * bs;

    vector<double> paddedA(np * mp, 0.0);
    for(int i = 0; i < M; ++i) {
        copy(A + i * N, A + i * N + N, paddedA.data() + i * np);
    }

    vector<double> paddedB(np * mp, 0.0);
    for(int i = 0; i < N; ++i) {
        copy(B + i * M, B + i * M + M, paddedB.data() + i * mp);
    }

    vector<double> paddedRes(mp * mp, 0.0);

    int blocksM = mp / bs;
    int blocksN = mp / bs;

    vector<double> blocktemp(bs * bs);
    for(int i = 0; i < blocksM; ++i) {
        for(int j = 0; j < blocksM; ++j) {
            for(int k = 0; k < blocksN; k ++){
                Strassenmatrix(paddedA.data() + i * bs * np + k * bs, paddedB.data() + k * bs * mp + j * bs, blocktemp.data(), np, mp, bs, bs);
            }

            for (int r = 0; r < bs; ++r) {
                for (int c = 0; c < bs; ++c) {
                    paddedRes[(i * bs + r) * mp + j * bs + c] += blocktemp[r * bs + c];
                }
            }
        }
    }

    for (int i = 0; i < M; ++i) {
        copy(paddedRes.data() + i * np, paddedRes.data() + i * np + M, res + i * M);
    }
}
void matrixSelfAddition(double* A, double* B, int M, int N) {
    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < M; ++j) {
            A[i * M + j] += B[i * M + j];
        }
    }
}



