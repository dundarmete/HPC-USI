// HPC Class: MPI Basics
// Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>

// INFO:
// An example of MPI (basic) program flow
// compile with makefile

// TODO:
// 1) Comment on what the program is doing. (try running "mpirun -np 2 ./main.exe")
// 2) Compare this program to the following code:
//    for (size_t i = 0; i < val.size(); i++){
//        val[i]=some_func(i);
//    }

#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <vector>

double some_func(int i) {
  sleep(1);
  return -1;
}

int main() {

  int size, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int n = size;
  std::vector<double> val(n, 0);

  printf("(Rank %d ) Before evaluation.\n", rank);
  for (int i = 0; i < val.size(); i++) {
    printf("%f ", val[i]);
  }
  printf("\n");

  val[rank] = some_func(rank);
  
  MPI_Barrier(MPI_COMM_WORLD);

  printf("(Rank %d ) After evaluation.\n", rank);
  for (int i = 0;i < val.size(); i++) {
    printf("%f ", val[i]);
  }
  printf("\n");

  MPI_Allreduce(MPI_IN_PLACE, &val[0], n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

  printf("(Rank %d ) After MPI_Allreduce.\n", rank);

  for (int i = 0; i < val.size(); i++) {
    printf("%f ", val[i]);
  }
  printf("\n");

  MPI_Finalize();
  return 0;
}
