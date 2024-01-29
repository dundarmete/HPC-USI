// HPC Class: OMP
// Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>

// INFO:
// basics usage of openMP, how to (and not to) implement reduction

// TODO:
// 1) Execute the function by setting the envirment variable OMP_NUM_THREADS to 1,2 and 4. (export OMP_NUM_THREADS=2; ./main.exe)
// 2) Comment on what you would expect and what you observe.

#include <omp.h>
#include <iostream>


int main() {

  int n = 1e6;
  int max_iter = 100;

  double *a = new double[n];
  double *b = new double[n];

  // Initialize the vectors with some values
  for (int i = 0; i < n; i++) {
    a[i] = double(i+1);
    b[i] = 1.0 / double(i+1);
  }

  long double res;
  double time_start;

  // serial execution
  time_start = omp_get_wtime();
  for (int itr = 0; itr < max_iter; itr++) {
    res = 0.0;
    for (int i = 0; i < n; i++) {
      res += a[i] * b[i];
    }
  }
  std::cout << "Serial:        time=" << omp_get_wtime() - time_start << " sec" << ", res="<<res << std::endl;

  // critical
  time_start = omp_get_wtime();
  for (int itr = 0; itr < max_iter; itr++) {
    res = 0.0;
    #pragma omp parallel for default(none) shared(a,b,n,res)
    for (int i = 0; i < n; i++) {
      #pragma omp critical
      res += a[i] * b[i];
    }
  }
  std::cout << "OMP Critical:  time=" << omp_get_wtime() - time_start << " sec" << ", res="<<res << std::endl;

  // atomic
  time_start = omp_get_wtime();
  for (int itr = 0; itr < max_iter; itr++) {
    res = 0.0;
    #pragma omp parallel for default(none) shared(a,b,n,res)
    for (int i = 0; i < n; i++) {
      #pragma omp atomic update
      res += a[i] * b[i];
    }
  }
  std::cout << "OMP Atomic:    time=" << omp_get_wtime() - time_start << " sec" << ", res="<<res << std::endl;

  // reduction
  time_start = omp_get_wtime();
  for (int itr = 0; itr < max_iter; itr++) {
    res = 0.0;
    #pragma omp parallel for default(none) shared(a,b,n) reduction(+ : res)
    for (int i = 0; i < n; i++) {
      res += a[i] * b[i];
    }
  }
  std::cout << "OMP Reduction: time=" << omp_get_wtime() - time_start << " sec" << ", res="<<res << std::endl;

  // De-allocate memory
  delete[] a;
  delete[] b;

  return 0;
}
