#include <algorithm>

#include "gemm.h"
#include "immintrin.h"
#include "matrix.h"

void gemm(const int M, const int N, const int K, const double *A, const int lda,
          const double *B, const int ldb, double *C, const int ldc,
          const double alpha, const double beta)
{
    int block_size = 8;
    double sum;

    Matrix T_B;
    init_matrix(&T_B, N, K);
    transpose(const Matrix *a, Matrix *b)

        for (int ii = 0; ii < M; ii += block_size)
    {
        for (int jj = 0; jj < N; jj += block_size)
        {
            for (int kk = 0; kk < K; kk += block_size)
            {
                for (int i = ii; i < std::min(ii + block_size, M); i += 4)
                {
                    for (int j = jj; j < std::min(jj + block_size, N); j += 4)
                    {
                        if (kk == 0)
                        {
                            sum = beta * C[i * ldc + j];
                        }
                        else
                        {
                            sum = C[i * ldc + j];
                        }

                        for (int k = kk; k < std::min(kk + block_size, K); k++)
                        {
                            sum += alpha * (A[i * lda + k] * B[k * ldb + j]);
                        }

                        C[i * ldc + j] = sum;
                    }
                }
            }
        }
    }
}
