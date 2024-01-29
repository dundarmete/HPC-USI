// HPC Class: example of avx intrinsics
// Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>


// INFO:
// Example of using avx intrinsics
// Compile cpp->exe: g++ -mavx -o main.exe main.cpp

// TODO
// 1) How many float can you fit in the register ?
// 2) What if we used doubles instead of floats ?
// 3) What if the vectors were of size 20 ?

#include <iostream>
#include <immintrin.h>  // For AVX intrinsics

int main() {
    float a[] = {1.0, 2.0, 3.0, 4.0};
    float b[] = {5.0, 6.0, 7.0, 8.0};
    float c[4]; 

    // Load arrays into 256-bit registers
    __m256 vec_a = _mm256_loadu_ps(a);
    __m256 vec_b = _mm256_loadu_ps(b);

    // Perform addition
    __m256 vec_c = _mm256_add_ps(vec_a, vec_b);

    // Store the result back into array c
    _mm256_storeu_ps(c, vec_c);

    // Print the result
    for (int i = 0; i < 4; ++i) {
        std::cout << c[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}