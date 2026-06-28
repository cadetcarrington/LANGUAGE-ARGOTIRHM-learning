#include "dgemm_optimized.h"

#include <algorithm>
#include <vector>

#if defined(_OPENMP)
#include <omp.h>
#endif

#if defined(__AVX2__) && defined(__FMA__)
#include <immintrin.h>
#endif

namespace {

constexpr int RM = 4;
constexpr int RN = 4;

void transposeB(const double* B, double* Bt, int cols, int K, bool parallel) {
#if defined(_OPENMP)
    if (parallel) {
#pragma omp parallel for schedule(static)
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < K; ++k) {
                Bt[j * K + k] = B[k * cols + j];
            }
        }
        return;
    }
#else
    (void)parallel;
#endif
    for (int j = 0; j < cols; ++j) {
        for (int k = 0; k < K; ++k) {
            Bt[j * K + k] = B[k * cols + j];
        }
    }
}

double dotScalarUnrolled(const double* a, const double* b, int K) {
    double s0 = 0.0;
    double s1 = 0.0;
    double s2 = 0.0;
    double s3 = 0.0;
    int k = 0;
    for (; k + 3 < K; k += 4) {
        s0 += a[k] * b[k];
        s1 += a[k + 1] * b[k + 1];
        s2 += a[k + 2] * b[k + 2];
        s3 += a[k + 3] * b[k + 3];
    }
    for (; k < K; ++k) {
        s0 += a[k] * b[k];
    }
    return (s0 + s1) + (s2 + s3);
}

#if defined(__AVX2__) && defined(__FMA__)
double hsum256(__m256d v) {
    __m128d hi = _mm256_extractf128_pd(v, 1);
    __m128d lo = _mm256_castpd256_pd128(v);
    __m128d sum = _mm_add_pd(lo, hi);
    __m128d high64 = _mm_unpackhi_pd(sum, sum);
    return _mm_cvtsd_f64(_mm_add_sd(sum, high64));
}

void computeFullBlockAvx(const double* A, const double* Bt, double* C,
                         int rows, int cols, int K, int ii, int jj) {
    (void)rows;
    __m256d c00 = _mm256_setzero_pd();
    __m256d c01 = _mm256_setzero_pd();
    __m256d c02 = _mm256_setzero_pd();
    __m256d c03 = _mm256_setzero_pd();
    __m256d c10 = _mm256_setzero_pd();
    __m256d c11 = _mm256_setzero_pd();
    __m256d c12 = _mm256_setzero_pd();
    __m256d c13 = _mm256_setzero_pd();
    __m256d c20 = _mm256_setzero_pd();
    __m256d c21 = _mm256_setzero_pd();
    __m256d c22 = _mm256_setzero_pd();
    __m256d c23 = _mm256_setzero_pd();
    __m256d c30 = _mm256_setzero_pd();
    __m256d c31 = _mm256_setzero_pd();
    __m256d c32 = _mm256_setzero_pd();
    __m256d c33 = _mm256_setzero_pd();

    const double* a0 = A + (ii + 0) * K;
    const double* a1 = A + (ii + 1) * K;
    const double* a2 = A + (ii + 2) * K;
    const double* a3 = A + (ii + 3) * K;
    const double* b0 = Bt + (jj + 0) * K;
    const double* b1 = Bt + (jj + 1) * K;
    const double* b2 = Bt + (jj + 2) * K;
    const double* b3 = Bt + (jj + 3) * K;

    int k = 0;
    for (; k + 3 < K; k += 4) {
        const __m256d av0 = _mm256_loadu_pd(a0 + k);
        const __m256d av1 = _mm256_loadu_pd(a1 + k);
        const __m256d av2 = _mm256_loadu_pd(a2 + k);
        const __m256d av3 = _mm256_loadu_pd(a3 + k);
        const __m256d bv0 = _mm256_loadu_pd(b0 + k);
        const __m256d bv1 = _mm256_loadu_pd(b1 + k);
        const __m256d bv2 = _mm256_loadu_pd(b2 + k);
        const __m256d bv3 = _mm256_loadu_pd(b3 + k);

        c00 = _mm256_fmadd_pd(av0, bv0, c00);
        c01 = _mm256_fmadd_pd(av0, bv1, c01);
        c02 = _mm256_fmadd_pd(av0, bv2, c02);
        c03 = _mm256_fmadd_pd(av0, bv3, c03);
        c10 = _mm256_fmadd_pd(av1, bv0, c10);
        c11 = _mm256_fmadd_pd(av1, bv1, c11);
        c12 = _mm256_fmadd_pd(av1, bv2, c12);
        c13 = _mm256_fmadd_pd(av1, bv3, c13);
        c20 = _mm256_fmadd_pd(av2, bv0, c20);
        c21 = _mm256_fmadd_pd(av2, bv1, c21);
        c22 = _mm256_fmadd_pd(av2, bv2, c22);
        c23 = _mm256_fmadd_pd(av2, bv3, c23);
        c30 = _mm256_fmadd_pd(av3, bv0, c30);
        c31 = _mm256_fmadd_pd(av3, bv1, c31);
        c32 = _mm256_fmadd_pd(av3, bv2, c32);
        c33 = _mm256_fmadd_pd(av3, bv3, c33);
    }

    double s00 = hsum256(c00);
    double s01 = hsum256(c01);
    double s02 = hsum256(c02);
    double s03 = hsum256(c03);
    double s10 = hsum256(c10);
    double s11 = hsum256(c11);
    double s12 = hsum256(c12);
    double s13 = hsum256(c13);
    double s20 = hsum256(c20);
    double s21 = hsum256(c21);
    double s22 = hsum256(c22);
    double s23 = hsum256(c23);
    double s30 = hsum256(c30);
    double s31 = hsum256(c31);
    double s32 = hsum256(c32);
    double s33 = hsum256(c33);

    for (; k < K; ++k) {
        const double ta0 = a0[k];
        const double ta1 = a1[k];
        const double ta2 = a2[k];
        const double ta3 = a3[k];
        const double tb0 = b0[k];
        const double tb1 = b1[k];
        const double tb2 = b2[k];
        const double tb3 = b3[k];
        s00 += ta0 * tb0;
        s01 += ta0 * tb1;
        s02 += ta0 * tb2;
        s03 += ta0 * tb3;
        s10 += ta1 * tb0;
        s11 += ta1 * tb1;
        s12 += ta1 * tb2;
        s13 += ta1 * tb3;
        s20 += ta2 * tb0;
        s21 += ta2 * tb1;
        s22 += ta2 * tb2;
        s23 += ta2 * tb3;
        s30 += ta3 * tb0;
        s31 += ta3 * tb1;
        s32 += ta3 * tb2;
        s33 += ta3 * tb3;
    }

    C[(ii + 0) * cols + jj + 0] = s00;
    C[(ii + 0) * cols + jj + 1] = s01;
    C[(ii + 0) * cols + jj + 2] = s02;
    C[(ii + 0) * cols + jj + 3] = s03;
    C[(ii + 1) * cols + jj + 0] = s10;
    C[(ii + 1) * cols + jj + 1] = s11;
    C[(ii + 1) * cols + jj + 2] = s12;
    C[(ii + 1) * cols + jj + 3] = s13;
    C[(ii + 2) * cols + jj + 0] = s20;
    C[(ii + 2) * cols + jj + 1] = s21;
    C[(ii + 2) * cols + jj + 2] = s22;
    C[(ii + 2) * cols + jj + 3] = s23;
    C[(ii + 3) * cols + jj + 0] = s30;
    C[(ii + 3) * cols + jj + 1] = s31;
    C[(ii + 3) * cols + jj + 2] = s32;
    C[(ii + 3) * cols + jj + 3] = s33;
}
#endif

void computeEdgeOrScalarBlock(const double* A, const double* Bt, double* C,
                              int rows, int cols, int K, int ii, int jj) {
    const int iEnd = std::min(ii + RM, rows);
    const int jEnd = std::min(jj + RN, cols);
    for (int i = ii; i < iEnd; ++i) {
        for (int j = jj; j < jEnd; ++j) {
            C[i * cols + j] = dotScalarUnrolled(A + i * K, Bt + j * K, K);
        }
    }
}

void computeBlock(const double* A, const double* Bt, double* C,
                  int rows, int cols, int K, int ii, int jj) {
#if defined(__AVX2__) && defined(__FMA__)
    if (ii + RM <= rows && jj + RN <= cols) {
        computeFullBlockAvx(A, Bt, C, rows, cols, K, ii, jj);
        return;
    }
#endif
    computeEdgeOrScalarBlock(A, Bt, C, rows, cols, K, ii, jj);
}

}  // namespace

void dgemmRowsSimdBlocked(const double* A, const double* B, double* C,
                          int rows, int cols, int K) {
    std::vector<double> Bt(static_cast<size_t>(cols) * K);
    transposeB(B, Bt.data(), cols, K, false);

    for (int ii = 0; ii < rows; ii += RM) {
        for (int jj = 0; jj < cols; jj += RN) {
            computeBlock(A, Bt.data(), C, rows, cols, K, ii, jj);
        }
    }
}

void dgemmRowsOpenMpBlocked(const double* A, const double* B, double* C,
                            int rows, int cols, int K) {
    std::vector<double> Bt(static_cast<size_t>(cols) * K);
    transposeB(B, Bt.data(), cols, K, true);

#if defined(_OPENMP)
#pragma omp parallel for collapse(2) schedule(static)
#endif
    for (int ii = 0; ii < rows; ii += RM) {
        for (int jj = 0; jj < cols; jj += RN) {
            computeBlock(A, Bt.data(), C, rows, cols, K, ii, jj);
        }
    }
}

void dgemmSimdBlocked(const double* A, const double* B, double* C,
                      int M, int N) {
    dgemmRowsSimdBlocked(A, B, C, M, M, N);
}

void dgemmOpenMpBlocked(const double* A, const double* B, double* C,
                        int M, int N) {
    dgemmRowsOpenMpBlocked(A, B, C, M, M, N);
}
