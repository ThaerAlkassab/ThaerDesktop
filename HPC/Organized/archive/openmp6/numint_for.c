#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>

double gettime() {
    return omp_get_wtime();
}

int main(int argc, char ** argv) {
    double a = 0;
    double b = M_PI / 2;
    int N = (double)atoll(argv[1]);

    double step = (b - a) / N;
    double step_half = step * 0.5;
    double res = 0;

    double start = gettime();

    int i;
    #pragma omp parallel for private(i) schedule(static) reduction(+:res)
    for (i = 0; i < N; i++) {
        res += cos(i * step + step_half);
    }
    res *= step;


    double end = gettime();
    double analytic = sin(b);
    printf("%16.18f\t", fabs(analytic - res));
    printf("%f\n", end - start);

    return 0;
    //gcc -O3 -lm -fopenmp -Wall -o numint_for numint_for.c 
    //OMP_NUM_THREADS=1000 ./numint
}