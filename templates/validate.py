import random as rng
import itertools as it
import collections as col
import heapq as hq
import sys
import copy as cp
import functools as ft
import math
sys.setrecursionlimit(10**9)


def dump_impl(*objects):
    print(*objects, file=sys.stderr)


def dump_dummy(*objects):
    pass


dump = dump_impl if "DEBUG" in sys.argv else dump_dummy


def odd(n): return n & 1


def even(n): return not odd(n)


def joinToString(iterable, sep: str = "", prefix: str = "", postfix: str = "") -> str:
    return prefix + sep.join(map(str, iterable)) + postfix

if True:
    print("OK")
    exit(0)
else:
    print("NG")
    exit(1)

