# HPC Class: Example of mpi4py
# Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>

# INFO:
# An example mpi4py point-to-point 
# installing mpi4py: pip3 install mpi4py
# running: mpirun -np 2 python3 main.py

# TODO:
# 1) Comment on what the program is doing.
# 2) Run the program on 2 and 4 processes.
# 3) Do you see a problem when running with 1 process?

from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

data=np.zeros(10)

if rank == 0:
    comm.send(np.ones(10), dest=1, tag=100)
elif rank == 1:
    data=comm.recv(source=0, tag=100)
    
    
print(data)