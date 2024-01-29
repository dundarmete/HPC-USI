// HPC Class: MPI Basics
// Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>

// INFO:
// An example MPI point-to-point communication. 
// compile with makefile

// TODO:
// 1) Comment on what the program doing. 
// 2) Run the program on 1, 2 and 3 processes.
// 3) Do you see a problem when running with 1 process?
// 4) Does the order of MPI_Recv and MPI_Send matter ? 

#include <cmath>
#include <vector>
#include <iostream>
#include <mpi.h>

int main(){

    int size, rank;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int sendbuf=0;
    int recvbuf=0;

    int recvbuf_size=1;
    int sendbuf_size=1;

    int destination;
    int source;

    int tag=1;

    if (rank == 0) {
        sendbuf=100;
    }else if(rank == 1) {
        sendbuf=900;
    }

    if (rank == 0) {
        destination=1;
        source=1;
        // Note order of MPI_Send and MPI_Recv
        MPI_Send(&sendbuf,sendbuf_size,MPI_INT,destination,tag,MPI_COMM_WORLD);
        MPI_Recv(&recvbuf,recvbuf_size,MPI_INT,source     ,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
     }
     else if(rank == 1) {
        destination=0;
        source=0;
        // Note the order of MPI_Recvand MPI_Send 
        MPI_Recv(&recvbuf,recvbuf_size,MPI_INT,source      ,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Send(&sendbuf,sendbuf_size,MPI_INT,destination ,tag,MPI_COMM_WORLD);
     }

    std::cout<<"(Rank "<<rank<<") recvbuf="<< recvbuf<<std::endl;

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();
    return 0;
}

