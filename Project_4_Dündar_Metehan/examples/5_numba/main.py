# HPC Class: Example of NUMBA
# Author: Aryan Eftekhari <aryan.eftkehari@gmail.com>

# INFO:
# An example numba
# installing numba: pip3 install numba
# running: python3 main.py

# TODO:
# 1) Comment on what the program is doing and the amount of parallelization.
# 2) Compare this to how OpenMP made reductions.

from numba import jit,prange
import random
import time

# Base function
def monte_carlo_pi(nsamples):
    acc = 0
    for i in range(nsamples):
        x = random.random()
        y = random.random()
        if (x ** 2 + y ** 2) < 1.0:
            acc += 1
    return 4.0 * acc / nsamples

# Just-in-time compilation of this function
@jit(nopython=True)
def jit_monte_carlo_pi(nsamples):
    acc = 0
    for i in range(nsamples):
        x = random.random()
        y = random.random()
        if (x ** 2 + y ** 2) < 1.0:
            acc += 1
    return 4.0 * acc / nsamples

# Just-in-time compilation which is parallelized
@jit(nopython=True, parallel=True)
def prl_jit_monte_carlo_pi(nsamples):
    acc = 0
    for i in prange(nsamples):
        x = random.random()
        y = random.random()
        if (x ** 2 + y ** 2) < 1.0:
            acc += 1
    return 4.0 * acc / nsamples

t=time.time()
val = monte_carlo_pi(50000000)
print('base time=',time.time()-t,' value=',val)

t=time.time()
val = jit_monte_carlo_pi(50000000)
print('jit time=',time.time()-t,' value=',val)

t=time.time()
val = prl_jit_monte_carlo_pi(50000000)
print('prl time=',time.time()-t,' value=',val)