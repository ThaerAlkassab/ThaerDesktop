#include <stdio.h>
#include <stdlib.h>

void printout(double t, double *T, int N){
    int i;
    int imax = 10;
    
    printf("%8.3f", t);
    for(i=0;i<imax;i++){
        int idx = i*(N+1)/(imax-1)-1;
        double Ti = T[idx];
        printf("%7.2f",Ti - 273.0);
    }
    printf("\n");
}

int main( int argc, char ** argv)
{
    int i; //indexing space
    int t; //indexing time
    int N = 1024; //number of cells
    int time = 5120000; //timesteps
    int print_time = time/20;
    
    double Tinit = 300.0; //Initial temperature in K
    double T1 = 1000.0; //BC Hot in K
    double T2 = 200.0; //BC cold in K
    
    double dx = 0.01; //size of cells in m
    double dt = 0.001; // size of timesteps
    
    double alpha = 0.03; //conduction coefficient
    
    double k = alpha * dt / dx /dx;
    
    double *T = (double *) malloc( (N+2) * sizeof(double)) +1 ;
    double *Dt = (double *) malloc(N * sizeof(double));
    
    //Setup initial condition
    #pragma omp parallel for schedule(static) private(i)
    for (i = 0;i<N;i++){
        T[i] = Tinit;
    }
    //Setup boundary conditions
    T[-1] = T1;
    T[N] = T2;
    
    //Do diff eq
    for(t=0;t<time;t++){
        //printout
        if(t % print_time == 0){
            printout(t,T,N);
        }
        
        //calculate change in temperature
        #pragma omp parallel for schedule(static) private(i)
        for(i=0;i<N;i++){
            Dt[i] = k*(T[i+1] + T[i-1] - 2*T[i]);
        }
        //update temperature
        #pragma omp parallel for schedule(static) private(i)
        for(i=0;i<N;i++){
            T[i] += Dt[i];
        }
    }
    printout(time,T,N);
    free(Dt);
    free(T-1);
    
    
    return 0;
}