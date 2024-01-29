// HPC Class: OMP
// Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>

// INFO:
// basics usage of openMP, scheduling ... static vs dynamics

// TODO:
// 1) Run the program with export OMP_NUM_THREADS=4; time ./main.exe 
// 2) Experiment with regular_workload and irregular_workload
// 3) Experiment with static vs dynamic scheduling

#include <omp.h>
#include <iostream>
#include <vector>
#include <unistd.h>

void regular_workload(int i){
  sleep(1);
}

void irregular_workload(int i){
  if(i>3){
    sleep(1);
  }
}


int main() {

  int N=8;
  int T=omp_get_max_threads();
  std::vector<double> time_reg(T,0.0);

  double t_total = omp_get_wtime();

  #pragma omp parallel for default(none) shared(time_reg,N) schedule(static)
  for (int i = 0; i < N; i++){
    double t = omp_get_wtime();

    regular_workload(i);

    time_reg[omp_get_thread_num()]+= omp_get_wtime()  - t;

    printf("itr %d -> tid %d \n",i,omp_get_thread_num());
  }

  t_total = omp_get_wtime()-t_total;
    
  printf("Time = ");
  for (int i = 0; i < T; i++){
    printf("%f ",time_reg[i]);
  }
  printf("\n");
  printf("Total %f\n",t_total);

  return 0;
}