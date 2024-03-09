#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <mpi.h>

double gettime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + 0.000001 * tv.tv_usec;
}

int main(int argc, char ** argv) {
    srand(time(0));

    double a = 0.0;
    double b = M_PI / 2.0;
    int N = atoll(argv[1]);
    double res = 0;
    double dx = (b-a) / N;
    double dx_half = dx * 0.5;

    double start = gettime();
    int i = 0;
    double myres = 0.0;
    for (i=0; i < N; i++) {
        myres += cos(i*dx + dx_half);
    }
    res += myres;
    res *= dx;
    double end = gettime();

    double err = res - 1;
    printf("%d \t", N);
    printf("%16.18f \t", fabs(err));
    printf("%16.18f \n", end-start);

    return 0;
}

//module list
//module avail
//module add mpi/openmpi-x86_64
//mpicc -O3 -lm -Wall -o numint numint.c
//mpirun -n 41 numint 100
//mpirun --map-by core -n 1 ./numint 100
//mpirun -n 1 master : -n 1 slave1 : -n 1 slave2