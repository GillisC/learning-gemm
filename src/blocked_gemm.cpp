#include <iostream>

#include "gemm.h"

void gemm(const int M, const int N, const int K, const double *A, const int lda,
          const double *B, const int ldb, double *C, const int ldc)
{
    int block_size = 32;
    int total = block_size * block_size + 2 * (block_size * K);
    std::cout << "Memory needed for each block: " << total << "\n";

    int block_i, block_j;

    block_i = M / block_size;
    block_j = N / block_size;

    std::cout << "rows of blocks: " << block_i
              << ", cols of blocks: " << block_j << std::endl;

    for (int ii = 0; ii < block_i; ii += block_size)
    {
        for (int jj = 0; jj < block_j; jj += block_size)
        {
            int block_00 = ii * block_i * block_size + jj * block_size;
            for (int i = 0; i < block_size; i++)
            {
                for (int j = 0; j < block_size; j++)
                {
                    double sum = 0.0;
                    for (int k = 0; k < K; k++)
                    {
                        sum += A[block_00 + i * lda + k] *
                               B[block_00 + k * ldb + j];
                    }
                    C[block_00 + i * ldc + j] = sum;
                }
            }
        }
    }
}
