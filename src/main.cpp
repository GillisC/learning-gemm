#include <chrono>
#include <cstdlib>
#include <iostream>
#include <unordered_map>

#include "gemm.h"
#include "matrix.h"

struct Timer
{
    static void begin_timing(const std::string &section_name)
    {
        times[section_name] = std::chrono::high_resolution_clock::now();
    }

    static void end_timing(const std::string &section_name)
    {
        if (times.find(section_name) != times.end())
        {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    end_time - times[section_name])
                    .count();
            std::cout << "Section: [ " << section_name << " ] took " << duration
                      << " ms." << std::endl;
        }
        else
        {
            std::cout << "Section: [ " << section_name << " ] not found"
                      << std::endl;
        }
    }

   private:
    static std::unordered_map<std::string,
                              std::chrono::high_resolution_clock::time_point>
        times;
};

std::unordered_map<std::string, std::chrono::high_resolution_clock::time_point>
    Timer::times;

int main()
{
    // Matrix a_t;
    // Matrix b_t;
    // Matrix c_t;
    //
    // int m = 2;
    // int n = 2;
    // int k = 2;
    //
    // double a_data[] = {1.0, 2.0, 3.0, 4.0};
    // double b_data[] = {1.0, 2.0, 3.0, 4.0};
    //
    // init_matrix_with_data(&a_t, m, k, a_data);
    // init_matrix_with_data(&b_t, k, n, b_data);
    // init_matrix(&c_t, m, n);
    //
    // gemm_wrapper(&a_t, &b_t, &c_t);
    //
    // print_matrix(&c_t);

    Matrix a;
    Matrix b;
    Matrix c;

    int N = 1024;
    int M = 1024;
    int K = 1024;

    init_random_matrix(&a, M, K);
    init_random_matrix(&b, K, N);

    init_matrix(&c, M, N);

    Timer::begin_timing("gemm");
    gemm_wrapper(&a, &b, &c);
    Timer::end_timing("gemm");

    return 0;
}
