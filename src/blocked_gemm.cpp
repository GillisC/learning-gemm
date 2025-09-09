#include <algorithm>
#include <iostream>

#include "gemm.h"

void gemm(const int M, const int N, const int K, const double *A, const int lda,
          const double *B, const int ldb, double *C, const int ldc)
{
    int block_size = 4;
    // int total = block_size * block_size + 2 * (block_size * K);
    // std::cout << "Memory needed for each block: " << total << "\n";

    for (int ii = 0; ii < M; ii += block_size)
    {
        for (int jj = 0; jj < N; jj += block_size)
        {
            for (int kk = 0; kk < K; kk += block_size)
            {
                for (int i = ii; i < std::min(ii + block_size, M); i++)
                {
                    for (int j = jj; j < std::min(jj + block_size, N); j++)
                    {
                        double sum = C[i * ldc + j];
                        for (int k = kk; k < std::min(kk + block_size, K); k++)
                        {
                            sum += A[i * lda + k] * B[k * ldb + j];
                        }
                        C[i * ldc + j] = sum;
                    }
                }
            }
        }
    }
}
