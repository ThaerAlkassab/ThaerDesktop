#!/usr/bin/python3
def print_out(t,T,N):
    imax = 10
    res = []
    for i in range (0,imax):
        idx = i*(N+1)//(imax-1)
        Ti = T[idx] - 273.0
        res.append(float(Ti))
    print(t,res)

def main():
    
    N=1024
    time = 512000
    print_time = time//20

    Tinit = 300.0
    T1 = 1000.0
    T2 = 200.0

    dx = 0.01
    dt = 0.001

    alpha = 0.03
    k = alpha * dt / dx**2

    T = [0] * (N+2)
    
    #Setup initial condition
    for i in range(1,N+1):
        T[i] = Tinit

    T[0] = T1
    T[N+1] = T2

    for t in range(0,time):
        if t % print_time == 0:
            print_out(t,T,N)

        temp_v = T[0]

        for i in range(1,N+1):
            temp_dt = k * (T[i+1] + temp_v - 2*T[i])
            temp_v = T[i]
            T[i] += temp_dt

    print_out(time,T,N)
            
    
main()