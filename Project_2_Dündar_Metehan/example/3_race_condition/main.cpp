// HPC Class: OMP
// Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>

// INFO:
// basics usage of openMP, race condition

// TODO:
// 1) Execute the function by setting the envirment variable OMP_NUM_THREADS to 1 and >1. (export OMP_NUM_THREADS=2; ./main.exe)
// 2) Comment on what you would expect and what you observe.

#include <omp.h>
#include <iostream>

int main() {

  double sum=0.0;
  double b=5.0;

  int N = 1e9;
  
  // you can fix this by no setting sum as shared variable, but rather as reduction variable i.e., reduction(+:sum)
  #pragma omp parallel for default(none) shared(b,sum,N)
  for (int i = 0; i < N; i++){
    sum+= 5.0/b;
  }
  
  if(int(sum)!=N){
    std::cout<< "Something is wrong!" <<std::endl;
  }

  std::cout<< sum <<std::endl;

  return 0;
}