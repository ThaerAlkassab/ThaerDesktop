#!/usr/bin/python3
import math # need for pi, cos
import sys
import time

a = 0
b = math.pi/2
N = int(sys.argv[1])

xi = a
res = 0

# loop over subintervals
start = time.time()
for i in range(0,N):
# sum the spaces of the subintervals
    xi2 = xi + (b-a)/N
    res = res + ( xi2 - xi ) * math.cos( (xi2 + xi)/2 )
    xi = xi2
end = time.time()

# print results
print(f"Results: {res}")
# compare with analytic result (1)
print(f"Error: {res - 1}")
print(f"Time: {end - start}")
