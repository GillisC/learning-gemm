#include <cstdlib>
#include <iostream>

#include "gemm.h"
#include "matrix.h"

int main()
{
    Matrix a;
    Matrix b;
    Matrix c;

    double a_data[] = {1, 2, 3, 4};
    double b_data[] = {1, 2, 3, 4};

    init_matrix_with_data(&a, 2, 2, a_data);
    init_matrix_with_data(&b, 2, 2, b_data);
    init_matrix(&c, 2, 2);

    print_matrix(&a);
    print_matrix(&b);

    gemm_wrapper(&a, &b, &c);
    print_matrix(&c);

    return 0;
}
