from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

# Compute the dimensions for the 2D grid
dims = MPI.Compute_dims(size, [0, 0])

# Create a Cartesian topology
cart_comm = comm.Create_cart(dims, periods=[True, True])

# Get Cartesian coordinates and rank in the new communicator
coords = cart_comm.Get_coords(rank)
print(f"Rank {rank}: Cartesian Coordinates = {coords}")

# Determine neighbors
north, south = cart_comm.Shift(0, 1)
east, west = cart_comm.Shift(1, 1)

# Exchange ranks
data_west = cart_comm.sendrecv(rank, source=west, dest=east)
data_east = cart_comm.sendrecv(rank, source=east, dest=west)
data_south = cart_comm.sendrecv(rank, source=south, dest=north)
data_north = cart_comm.sendrecv(rank, source=north, dest=south)

# Output topology information
print(f"Rank {rank}: Neighbors - North: {north}, South: {south}, East: {east}, West: {west}")

# Verify ranks
assert data_west  == west
assert data_east  == east
assert data_south == south
assert data_north == north
print(f"Rank {rank}: Ranks are exchanged succesfully")

cart_comm.Free()
