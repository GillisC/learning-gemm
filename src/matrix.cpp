#include "matrix.h"

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
        total_bytes = (rows * stride) * sizeof(double);
        m->data = (double*) (aligned_alloc(alignment_factor, total_bytes));
        m->stride = stride;
    }

    m->allocation_size = total_bytes;
    m->rows = rows;
    m->columns = columns;
}

void init_matrix_with_data(Matrix* m, int rows, int columns, double* data)
{
    init_matrix(m, rows, columns);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            m->data[i * m->stride + j] = data[i * columns + j];
        }
    }
}

void print_matrix(Matrix* m)
{
    std::cout << "\n";
    for (int i = 0; i < m->rows; ++i)
    {
        for (int j = 0; j < m->columns; ++j)
        {
            std::cout << m->data[i * m->stride + j] << " ";
        }
        std::cout << "\n";
    }
}
