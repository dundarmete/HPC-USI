// HPC Class: OMP
// Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>

// INFO:
// basics usage of firstprivate and lastprivate

// TODO:
// 1) Run the program
// 2) Experiment with private(x) and firstprivate(x)
// 3) Experiment by also adding lastprivate(x)


#include <omp.h>
#include <iostream>

int main() {
    int x = 10;

    #pragma omp parallel for private(x)
    for (int i = 0; i < 5; ++i) {
        x = x*2;  // Calculate squares
        
        // Output x from each thread
        #pragma omp critical 
        {
            std::cout << "Thread " << omp_get_thread_num() 
                      << ", i = " << i
                      << ": x = " << x << std::endl;
        }
    }
    // Output x from master thread (unchanged)
    std::cout << "Master thread: x = " << x << std::endl;
    
    return 0;
}
