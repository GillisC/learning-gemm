# General Matrix Multiply (GEMM)
GEMM is a algorithm to perform matrix multiplication. This repository aims to explain and benchmark different implementations of GEMM with the goal of understanding how performance is affected.

## Goal
The goal is to compute the following:
```math
C \leftarrow \alpha AB  + \beta C
```

## Implementations
The following implementations are included:
1. Naive
2. Blocked
3. AVX2
4. AVX512
5. Parallel SIMD

## Matrix
The following variables will be used to describe how the below implementations work.
- 
### Naive
The naive implementation works as follows: Given two input matrices A & B, and an output matrix C (row-major) we iterate over each cell in C. For each iteration we iterate over k 
