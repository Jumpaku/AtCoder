import random as rng
import itertools as it
import collections as col
import heapq as hq
import sys
import copy as cp
sys.setrecursionlimit(10**9)
input = sys.stdin.readline


def dump_impl(*objects):
    print(*objects, file=sys.stderr)


def dump_dummy(*objects):
    pass


dump = dump_impl if "DEBUG" in sys.argv else dump_dummy


def odd(n): return n & 1


def even(n): return not odd(n)

if len(sys.argv) > 1:
    rng.seed(int(sys.argv[1]))

#N = 20
#K = rng.randint(1, N)

