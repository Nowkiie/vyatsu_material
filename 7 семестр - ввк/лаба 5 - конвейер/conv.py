from math import factorial as fact
from functools import reduce


tt = [8e-9, 3e-9, 6e-9, 8e-9, 6e-9, 6e-9, 9e-9]
L = 64 # 32
ti = 0
ts = 46e-9
tc = 9e-9 #max(tt)
n = 7


def P(L, n, tc, ti):
	return L / (tc * (L + n - 1) + ti)

def d(f, r):
	return f * r + (1 - r)

def tstart(ti, tc, n):
	return ti + n * tc

def E(L, tscalar, tstart, tc):
	return L * tscalar / (tstart + (L - 1) * tc)

print(f'P = {P(L, n, tc, ti)}')

print(f'd = 1')

print(f'tstart = {tstart(ti, tc, n)}')

print(f'E = {E(L, ts, tstart(ti, tc, n), tc)}')

p = P(64, 7, 9e-9, 15e-9) + 101587301+P(64, 7, 9e-9, 18e-9)
print(f'P = {p / 3}')

e = E(64, 46e-9, tstart(15e-9, 9e-9, 7), 9e-9) +\
    E(64, 48e-9, tstart(18e-9, 9e-9, 7), 9e-9) +\
    E(64, 46e-9, tstart(15e-9, 9e-9, 7), 9e-9)
print(f'E = {e / 3}')
