#!/bin/bash

# Set the number of workers for scaling study
workers=(2 4 8 16)

# Set the workload divisions for scaling study
workloads=(50 100)

# Loop over matrix sizes
for worker in "${workers[@]}"; do
    for workload in "${workloads[@]}"; do
        mpiexec -n $worker --oversubscribe python3 manager_worker.py 4001 4001 $workload
    done
done
