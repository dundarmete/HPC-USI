// HPC Class: OMP
// Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>

// INFO:
// basics usage of openMP and specifying the number of threads.

// Note: Using printf() instead of std::cout is not guaranteed to keep parallel text prints more organized. There are no difference in the computation!

// TODO:
// 1) Execute the function by setting the envirment variable OMP_NUM_THREADS to 4. (export OMP_NUM_THREADS=4; ./main.exe)
// 2) Comment on how you see how the maximum number of threads change. 

#include <omp.h>
#include <iostream>

int main() {

  #pragma omp parallel
  {
    printf("parallel region 1: We are %d threads, I am thread %d.\n", omp_get_num_threads(), omp_get_thread_num());
    
  }

  omp_set_num_threads(2);

  #pragma omp parallel num_threads(3)
  {
    printf("parallel region 2: We are %d threads, I am thread %d.\n", omp_get_num_threads(), omp_get_thread_num());
  }

  #pragma omp parallel
  {
    int thread_id = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    printf("parallel region 3: We are %d threads, I am thread %d.\n", omp_get_num_threads(), omp_get_thread_num());
  }

  return 0;
}

