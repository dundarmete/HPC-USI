#!/bin/bash

# Define matrix sizes
matrix_sizes=(128 256 512 1024)

# Define MPI ranks
mpi_ranks=(1 2 4 8 12 16 32)

# Loop over matrix sizes
for size in "${matrix_sizes[@]}"; do
    for rank in "${mpi_ranks[@]}"; do
        mpiexec -n $rank --oversubscribe python3 main.py $size 100 0.005 verbose
    done
done
