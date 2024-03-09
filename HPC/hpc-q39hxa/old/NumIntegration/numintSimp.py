#!/usr/bin/python3
import math #needed for pi and cos
import sys

import time

# Define limits a and b
a = 0
b = math.pi/2

#get resolution from user,number of subintervals
n = int(sys.argv[1])

#define fuction
f = lambda x : math.cos(x)
res = 0
start = time.time()
#Loop over subintervals
#sum the value of one of the methods for each interval
h = (b-a)/n
multi = [4,2]
xi = a + h
for i in range(0,n):
    res = res + (multi[0] * f(xi))
    multi = [multi[1],multi[0]]
    xi = xi + h
res = (1/3)*h*(res+f(a)+f(b))
end = time.time()
#print results
print(f"Results: {res}")
#Compare with analytic result (1)
print(f"Error: {res-1}")
print(f"Time: {end - start}")
