#include <cstddef>
#include <cstdlib>
#include <iostream>

size_t padded_cols(size_t cols, size_t element_size, size_t align_bytes)
{
    size_t bytes = cols * element_size;
    size_t padded_bytes =
        ((bytes + align_bytes - 1) / align_bytes) * align_bytes;
    return padded_bytes / element_size;
}

void init_matrix(Matrix* m, int rows, int columns)
{
    size_t alignment_factor = 32;
    int total_bytes;

    if ((columns * sizeof(double)) % alignment_factor == 0)
    {
        total_bytes = (rows * columns) * sizeof(double);
        m->data = (double*) (aligned_alloc(alignment_factor, total_bytes));
        m->stride = columns;
    }
    else
    {
        size_t stride = padded_cols(columns, sizeof(double), alignment_factor);
        std::cout << stride << "\n";
        total_bytes = (rows * stride) * sizeof(double);
        m->data = (double*) (aligned_alloc(alignment_factor, total_bytes));
        m->stride = stride;
    }

    m->allocation_size = total_bytes;
    m->rows = rows;
    m->columns = columns;
}

int main()
{
    Matrix m1;
    Matrix m2;

    init_matrix(&m1, 8, 8);
    init_matrix(&m2, 8, 7);

    std::cout << "m1 allocation size: " << m1.allocation_size << std::endl;
    std::cout << "m2 allocation size: " << m2.allocation_size << std::endl;

    return 0;
}
