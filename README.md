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

The following variables describe the dimensions of the matrices:
- $M$: The number of rows in $A$.
- $N$: The number of columns in $B$.
- $K$: The number of columns in $A$ and the number of rows in $B$. 

$\beta$ allows the reuse of what is already in $C$:
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
We iterate over each cell in $C$ (row-major). For each cell C we iterate over $k < K$ in which we accumalate $A_{ik} \cdot B_{kj}$ and write that sum back into $C_{ij}$.

#### Notes
Using this approach we are able to access the content of $A$ in a continouos manner, meaning that the CPU can reuse content from the cache better. Accesses to $B$ is not continouous on the other hand where we hop from column to column. If the content of the matrix is floats for example then a cache line would contain 16 floats where not a single one would be reused afterwards in an effective manner. This leads to many more reads from main memory increasing the execution time for larger matrices substantially.


### Blocked
The blocked approach aims to improve cache utilization by using blocking. Blocking in the case of GEMM means splitting the computation of C over several blocks. The following is an implementation of blocked GEMM:
```cpp
void gemm(const int M, const int N, const int K, const double *A, const int lda,
          const double *B, const int ldb, double *C, const int ldc)
{
    int block_size = 8;

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
```
Here we iterate over $ii$ and $jj$ which can be thought of as the current block in $C$ that we are trying to compute. $kk$ acts as the block that moves vertically in $A$ and the block that moves horizontally in $B$. This part of the function can be thought of as the 'blocking' part. Then $ii$ and $jj$ iterate within these blocks and compute results and accumalates it into $C_{ij}$. Here we want to be able to fit the current block that is being computed in $C$ and the blocks that $kk$ move over in $A$ and $B$.
