#include "gemm.h"

void gemm(const int M, const int N, const int K, const double *A, const int lda,
          const double *B, const int ldb, double *C, const int ldc,
          const double alpha, const double beta)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < K; k++)
            {
                sum += A[i * lda + k] * B[k * ldb + j];
            }
            C[i * ldc + j] = (alpha * sum) + (beta * C[i * ldc + j]);
        }
    }
}
