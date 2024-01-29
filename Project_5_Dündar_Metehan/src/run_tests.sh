#!/bin/bash

# Define matrix sizes
matrix_sizes=("128 128" "256 256" "512 512" "1024 1024")

# Define MPI ranks
mpi_ranks=(1 2 4)

# Loop over matrix sizes
for size in "${matrix_sizes[@]}"; do
    for threads in {1..10}; do
        for ranks in "${mpi_ranks[@]}"; do
            export OMP_NUM_THREADS=$threads
            mpirun -np $ranks ./main $size 100 0.01
        done
    done
done
