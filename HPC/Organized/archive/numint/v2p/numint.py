#!/usr/bin/python3
import math # need for pi, cos
import sys
import time

a = 0
b = math.pi/2
N = int(sys.argv[1])
res = 0
dx = (b-a)/N
dxhalf = dx*0.5

# loop over subintervals
start = time.time()
for i in range(0,N):
# sum the spaces of the subintervals
    res += math.cos( i*dx+dxhalf )
res *= dx
end = time.time()

# print results
print(f"Results: {res}")
# compare with analytic result (1)
print(f"Error: {res - 1}")
print(f"Time: {end - start}")
