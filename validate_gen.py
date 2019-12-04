import itertools as it
import collections as col
import heapq as hq
import sys
import copy as cp
import random as rng
sys.setrecursionlimit(10**9)


def dump_impl(*objects):
    print(*objects, file=sys.stderr)


def dump_dummy(*objects):
    pass


dump = dump_impl if "DEBUG" in sys.argv else dump_dummy

if len(sys.argv) > 1:
    rng.seed(int(sys.argv[1]))

N = 20
K = rng.randint(1, N)
print(N, K)
for i in range(N):
    print(rng.randint(1, N))
