/****************************************************************
 *                                                              *
 * This file has been written as a sample solution to an        *
 * exercise in a course given at the CSCS-USI Summer School.    *
 * It is made freely available with the understanding that      *
 * every copy of this file must include this header and that    *
 * CSCS/USI take no responsibility for the use of the enclosed  *
 * teaching material.                                           *
 *                                                              *
 * Purpose: Parallel maximum using a ping-pong                  *
 *                                                              *
 * Contents: C-Source                                           *
 *                                                              *
 ****************************************************************/


#include <stdio.h>
#include <mpi.h>


int main (int argc, char *argv[])
{
    int my_rank, size;
    int snd_buf, rcv_buf;
    int right, left;
    int max, i;
    int comm_size;

    MPI_Status  status;
    MPI_Request request;


    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);


    right = (my_rank + 1 + size) % size;/* get rank of neighbor to your right */
    left  = (my_rank - 1 + size) % size;/* get rank of neighbor to your left */

    // Initialize snd_buf with my_rank
    snd_buf = my_rank;

    comm_size = size;

    // Initialize max with 0
    max = 0;

    for (i = 0; i < size; ++i) {
        MPI_Sendrecv(&snd_buf, 1, MPI_INT, right, 0, &rcv_buf, 1, MPI_INT, left, 0, MPI_COMM_WORLD, &status);

        // Update snd_buf with the received value
        snd_buf = rcv_buf;

        // Calculate the value based on the given function
        int value = (3 * snd_buf) % (2 * comm_size);

        // Update max if the calculated value is greater
        if (value > max) {
            max = value;
        }
    }

    printf ("Process %i:\tMax = %i\n", my_rank, max);

    MPI_Finalize();
    return 0;
}