#pragma once

#include <stdexcept>

#include "matrix.h"

/**
 * computes matrix multiplication of AxB and writes the result to C
 * @param M rows in A
 * @param N columns in B
 * @param K columns and rows in A and B respectively
 * @param A input matrix
 * @param lda the leading dimension in A
 * @param B input matrix
 * @param ldb the leading dimension in B
 * @param C output matrix
 * @param ldc the leading dimension in C
 *
 * @note due to memory alignment the ld(a,b,c) is used to find next row of
 * data
 */
void gemm(const int M, const int N, const int K, const double* A, int lda,
          const double* B, int ldb, double* C, int ldc);

inline void gemm_wrapper(const Matrix* A, const Matrix* B, Matrix* C)
{
    if (A->columns != B->rows || A->rows != C->rows || B->columns != C->columns)
    {
        throw std::invalid_argument("Matrix dimensions do not match for GEMM");
    }

    gemm(A->rows, B->columns, A->columns, A->data, A->stride, B->data,
         B->stride, C->data, C->stride);
}
