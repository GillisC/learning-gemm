#pragma once

#include <cstddef>

typedef struct
{
    double* data;
    int rows;
    int columns;
    int stride;
    size_t allocation_size;
} Matrix;

void init_matrix(Matrix* m, int rows, int columns);
void init_matrix_with_data(Matrix* m, int rows, int columns, double* data);

void print_matrix(Matrix* m);
