// HPC Class: MPI Basics
// Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>

// INFO:
// An example MPI program flow
// compile with makefile

// TODO:
// 1) Comment on what the program is doing.
// 2) Run the program on 1,2,4 processes.
// 3) What would be the program's runtime if you had 100 processes?

#include <cmath>
#include <vector>
#include <iostream>
#include <mpi.h>

int main(){

    int n = 1e4;
    std::vector<double> val(n,0);
    
    int size, rank;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double t=MPI_Wtime();

    int block_size = n/size;
    int start = rank*block_size;
    int end   = (rank+1)*block_size;
    if(rank==size-1){
        end=n;
    }
    for ( int i = start; i < end; i++){
        for ( int j=0; j < 1000; j++){
            val[i]+= std::sin(2 * 3.145 * double(j+i) / double(n));
        }
    }
    
    MPI_Allreduce( MPI_IN_PLACE, &val[0]  , n , MPI_DOUBLE  , MPI_SUM , MPI_COMM_WORLD);

    double sum=0;
    for ( int i = 0; i < val.size(); i++){
       sum+=val[i];
    }

    printf("(Rank %d) Time1=%f sum=%f \n",rank,MPI_Wtime() - t,sum);

    MPI_Finalize();
    return 0;
}

