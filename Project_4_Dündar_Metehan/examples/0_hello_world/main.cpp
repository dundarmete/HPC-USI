// HPC Class: MPI Basics
// Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>

// INFO:
// Hello world for MPI
// compile with: use makefile 

// TODO:
// 1) Run the program with 1,2 and 4 processes. 
// 2) Comment on the ordering of the output.

#include <mpi.h>
#include <iostream>

int main(){
    int size, rank;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::cout<<" Hello from rank "<< rank <<"/"<<size<<std::endl;
    MPI_Finalize();
    return 0;
}

