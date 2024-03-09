import time
import math # need for pi and cos
# define limits a and b
a=0
b=math.pi/2

# get resolotion
N  = int(input("subintervals: "))
dx=(b-a)/N

res=0
start = time.time()
for i in range(1,N-1):
    res+=2*math.cos(i*dx)
res*=(dx/2)
res+=((dx/2)*(math.cos(b)+math.cos(a)))
end = time.time()
print(res)
print(res-1)
print(end-start)