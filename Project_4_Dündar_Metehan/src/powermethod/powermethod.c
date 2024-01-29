/****************************************************************
 *                                                              *
 * This file has been written as a sample solution to an        *
 * exercise in a course given at the CSCS-USI Summer School.    *
 * It is made freely available with the understanding that      *
 * every copy of this file must include this header and that    *
 * CSCS/USI take no responsibility for the use of the enclosed  *
 * teaching material.                                           *
 *                                                              *
 * Purpose: : Parallel matrix-vector multiplication and the     *
 *            and power method                                  *
 *                                                              *
 * Contents: C-Source                                           *
 *                                                              *
 ****************************************************************/

#include "hpc-power.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void matVec(double* A, double* x, double* y, int N)
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    double* B = (double*)calloc(N/size, sizeof(double));
    for(int i=0; i<N/size; i++)
        for(int j=0; j<N  ; j++)
            B[i] += A[i*N + j] * x[j];
    MPI_Gather(B, N/size, MPI_DOUBLE, y, N/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    free(B);
}

double norm(double* x, int N)
{
    double res=.0;
    for(int i=0;i<N;++i)
        res += x[i]*x[i];
    return sqrt(res);
}

double powerMethod(double* A, int maxIter, int N) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status; 
    MPI_Request request;
    double *x = (double *) calloc(N, sizeof(double));
    if (rank == 0)
        for (int i = 0; i < N; i++)
            x[i] = (double) (rand() % 10) / 100;

    for (int i = 0; i < maxIter; ++i) {
        if (rank == 0) {
            double l2 = norm(x, N);
            for (int k = 0; k < N; ++k)
                x[k] /= l2;
        }
        double *iter = (double *) calloc(N, sizeof(double));
        matVec(A, x, iter, N);
        if (rank == 0) {
            for (int k = 0; k < N; ++k)
                x[k] = iter[k];
        }
    }
    return norm(x, N);
}

void generateMatrix(double* A, int N)
{
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    for(int i = 0; i < N / size; ++i){
        for(int j = 0; j < N; ++j){
            if(i == j)
                A[i * N + j] = 1.;
            if (abs(i - j) == 1)
                A[i * N + j] = 0.;
        }
    }
}

int main (int argc, char *argv[])
{
    int my_rank, size;
    int snd_buf, rcv_buf;

    MPI_Status  status;
    MPI_Request request;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 4096;
    double* A = (double*)calloc(N*N/size, sizeof(double));
    generateMatrix(A, N);

    double time = -hpc_timer();
    double res = powerMethod(A, 1000, N);
    time += hpc_timer();

    if(my_rank == 0) {
        printf("size = %i\n", size);
        printf("N    = %i\n", N);
        printf("time = %.4f\n", time);
    }

    free(A);
    MPI_Finalize();
    return 0;
}
