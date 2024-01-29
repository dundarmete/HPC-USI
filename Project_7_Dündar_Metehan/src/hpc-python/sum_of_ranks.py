from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

# Method 1: Pickle-based communication
sum1 = comm.reduce(rank, op=MPI.SUM, root=0)

# Method 2: Direct array data communication
buf = np.array(rank, dtype='i')
sum2 = np.empty(1, dtype='i')
comm.Reduce([buf, MPI.INT], sum2, op=MPI.SUM, root=0)

if rank == 0:
    print(f"Sum of all ranks using pickle-based communication: {sum1}")
    print(f"Sum of all ranks using direct array data communication: {sum2[0]}")
