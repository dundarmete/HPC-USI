#!/bin/bash

# Define matrix sizes
matrix_sizes=(128 256 512 1024)

# Define MPI ranks
mpi_ranks=(1 2 4 8 12 16 32)

# Loop over matrix sizes
for size in "${matrix_sizes[@]}"; do
    for rank in "${mpi_ranks[@]}"; do
        mpirun -n $rank --oversubscribe ./main $size 100 0.005
    done
done
