# General Matrix Multiply (GEMM)
GEMM is a algorithm to perform matrix multiplication. This repository aims to explain and benchmark different implementations of GEMM with the goal of understanding how performance is affected.

## Goal
The goal is to compute:
```math
C \leftarrow \alpha AB  + \beta C
```
Where:
- $A$: The first input matrix
- $B$: The second input matrix
- $C$: The output matrix
- $\alpha$ & $\beta$: Scales

$\alpha$ scales the result of $A \cdot B$:
- if $\alpha = 1$, nothing changes. 
- if $\alpha = 2$, the result is doubled. 
- if $\alpha = 1$, the result is halfed. 

Depending on the scale of $\beta$ GEMM allows the reuse of what is already in $C$:
```math
C_{ij} \leftarrow \alpha \sum_{p=1}^K A_{ip} B_{pj} + \beta C_{ij}^{old}
```
- if $\beta = 0$ old $C$ is ignored and overwritten. 
- if $\beta = 1$ old $C$ is added to the new product. 
- if $\beta = -1$ old $C$ is subtracted from the new product.


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
