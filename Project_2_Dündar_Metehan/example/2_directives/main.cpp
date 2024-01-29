// HPC Class: OMP
// Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>

// INFO:
// basics usage of openMP, examples of different directives

// TODO:
// 1) Execute the function by setting the envirment variable OMP_NUM_THREADS to 1,2,3,4. (export OMP_NUM_THREADS=4; ./main.exe)
// 2) Comment on  what you would expect and what you observe.

#include <omp.h>
#include <iostream>

int main() {

    #pragma omp parallel sections
    {
        #pragma omp section
        { 
            printf("Section: thread %d/%d in section 1\n", omp_get_thread_num(), omp_get_num_threads());
        }

        #pragma omp section
        { 
            printf("Section: thread %d/%d in section 2\n", omp_get_thread_num(), omp_get_num_threads());
        }
    }


    #pragma omp parallel 
    {
        printf("Parllel: thread %d/%d in parallel region (not a section)\n", omp_get_thread_num(), omp_get_num_threads());

    }

    #pragma omp parallel for default(shared)
    for (int i = 0; i < 4; i++){
        printf("For: thread %d/%d in for loop indx %d\n", omp_get_thread_num(), omp_get_num_threads(),i);
    }

  return 0;
}

