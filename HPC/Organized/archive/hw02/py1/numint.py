#!/usr/bin/python3
import math # need for pi, cos
import sys
import time

# define a, b
a = 0
b = math.pi / 2

# get resolution: number of subintervals
N = int(sys.argv[1])
#N = int(input('N: '))

step = (b - a) / N
step_half = step / 2
res = 0

start = time.time()

for i in range(0, N):
    res += math.cos((i * step + (i * step + step)) / 2)
res *= step
end = time.time()
    
analytic = math.sin(b)
print(str(abs(analytic-res)) + '\t' + str(end-start))