#ifndef DGEMM_OPTIMIZED_H
#define DGEMM_OPTIMIZED_H

void dgemmRowsSimdBlocked(const double* A, const double* B, double* C,
                          int rows, int cols, int K);
void dgemmRowsOpenMpBlocked(const double* A, const double* B, double* C,
                            int rows, int cols, int K);

void dgemmSimdBlocked(const double* A, const double* B, double* C,
                      int M, int N);
void dgemmOpenMpBlocked(const double* A, const double* B, double* C,
                        int M, int N);

#endif
