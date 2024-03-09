import numpy as np

def printout(t, T, N):
    out = ''
    imax = 10;
    out += str(t) + ' '
    for i in range(imax):
        idx = i*(N+1)//(imax-1)-1
        Ti = T[idx]
        out += str(Ti - 273.0) + ' '
        
    print(out + '\n')


N = 1024
time = 5120
printtime = time / 20

Tinit = 300.0
T1 = 1000.0
T2 = 200.0

dx = 0.01
dt = 0.001
alpha = 0.03

k = alpha * dt / dx / dx;

T = np.empty(N+2)
DT = 0.0;
v = 0.0;

T.fill(Tinit)
T[0] = T1;
T[N] = T2;

for t in range(1, time):
    if t % printtime == 0:
        printout(t, T, N)
            
    v = T[-1];
    for i in range(1, N):
        DT = k * (T[i+1] + v - 2*T[i])
        v = T[i]
        T[i] += DT
        
printout(time, T, N)
