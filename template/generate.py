import random as rng
import itertools as it
import collections as col
import heapq as hq
import sys
import copy as cp
import functools as ft
import math

sys.setrecursionlimit(10 ** 9)


def dump(*objects):
    if "DEBUG" not in sys.argv:
        return
    print(*objects, file=sys.stderr)


def odd(n): return n & 1


def even(n): return not odd(n)


def gcd_Olog(p, q):
    return p if (q == 0) else gcd_Olog(q, p % q)


def lcm_Olog(p, q):
    return p / gcd_Olog(q, p) * q


def joinToString(iterable, sep: str = "", prefix: str = "", postfix: str = "") -> str:
    return prefix + sep.join(map(str, iterable)) + postfix


def validate(*params):
    if "DEBUG" not in sys.argv:
        return
    dump("---------- Validate ----------")
    if not True:
        exit(1)
