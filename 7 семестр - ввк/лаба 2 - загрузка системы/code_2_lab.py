from math import factorial as fact
from functools import reduce


def p_0(R, N):
    num = R ** N
    den = fact(N - 1) * (N - R)
    s = sum((R ** n) / fact(n) for n in range(N))
    return 1 / (num / den + s)


def p_n(R, n, N):
    if n <= N:
        return p_0(R, N) * (R ** n) / fact(n)
    else:
        return p_0(R, N) * (R ** n) / (fact(N) * N ** (n - N))


def p_0_1(N, p):
    num = N ** (N - 1) * p ** N
    den = fact(N - 1) * (1 - p)
    s = sum((N ** i) * (p ** i) / fact(i) for i in range(N))
    return 1 / (num / den + s)


def l(N, p):
    num = N ** (N - 1) * p ** (N + 1)
    den = fact(N - 1) * (1 - p) ** 2
    return num/den 


t1 = p_n(4.3, 4, 6)
print(round(t1, 7))

t2 = p_n(2.3, 12, 6)
print(round(t2, 8))

t4 = p_0_1(6, 0.2642724)
print(round(t4, 8))

t3 = l(6, 0.1670401)
print(round(t3, 8))
