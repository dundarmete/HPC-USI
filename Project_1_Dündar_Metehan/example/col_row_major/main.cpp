// HPC Class: Loop reordering and contiguous data access
// Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>

// INFO:
// Example of the performance difference if "bad" loop
// ordering is used and the importance of contiguous data access patterns.
// Compile cpp->exe: g++ -o main.exe main.cpp

// TODO
// 1) Run the code. Why is there a difference in runtime?
// 2) Try compiling with the "-O3" flag, i.e., g++ -o main.exe main.cpp -O3. Explain.
// 3) Think of some ways to fix the issue (assuming the matrix is not symmetric).

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

double matrix_vector_multiply_row(double** A, const vector<double>& x, size_t n) {
    vector<double> result(n, 0.0);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            result[i] += A[i][j] * x[j];
        }
    }

    double val =0;
    for (size_t i = 0; i < n; ++i) {
        val+=result[i];
    }
    
    return val;
}

double matrix_vector_multiply_col(double** A, const vector<double>& x, size_t n) {
    vector<double> result(n, 0.0);

    for (size_t j = 0; j < n; ++j) {
        for (size_t i = 0; i < n; ++i) {
            result[i] += A[i][j] * x[j];
        }
    }

    double val =0;
    for (size_t i = 0; i < n; ++i) {
        val+=result[i];
    }
    return val;
}

int main() {
    // Matrix size
    size_t n = 4000;
    size_t K = 100;

    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    // Initialize a symmetric matrix with random numbers
    double** A = new double*[n];
    for (size_t i = 0; i < n; ++i) {
        A[i] = new double[n];
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i; j < n; ++j) {
            double val = dis(gen);
            A[i][j] = val;
            A[j][i] = val;  // Symmetric
        }
    }

    // Initialize vector x with random numbers
    vector<double> x(n);
    for (size_t i = 0; i < n; ++i) {
        x[i] = dis(gen);
    }

    // Perform matrix_vector_multiply_col
    auto start_time = high_resolution_clock::now();

    for (size_t i = 0; i < K; ++i) {
        matrix_vector_multiply_col(A, x, n);
    }
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);

    cout << "Average runtime for  matrix_vector_multiply_col" << K << " runs: " << (double)duration.count() / K << " ms" << endl;

    // Perform matrix_vector_multiply_row
    start_time = high_resolution_clock::now();

    for (size_t i = 0; i < K; ++i) {
        matrix_vector_multiply_row(A, x, n);
    }
    end_time = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end_time - start_time);

    cout << "Average runtime for  matrix_vector_multiply_row" << K << " runs: " << (double)duration.count() / K << " ms" << endl;

    // Cleanup
    for (size_t i = 0; i < n; ++i) {
        delete[] A[i];
    }
    delete[] A;

    return 0;
}
