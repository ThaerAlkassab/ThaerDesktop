#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>

double gettime() {
    return omp_get_wtime();
}

int main(int argc, char ** argv) {
    double a = 0;
    double b = M_PI / 2;
    double N = (double)atoll(argv[1]);
    //double N = 0.0;
    //scanf("%lf", & N);

    //trapezoid formula
    double step = (b - a) / N;
    double step_half = step * 0.5;
    double res = 0;

    double start = gettime();

    #pragma omp parallel
    {
        double myres = 0;
        int tid = omp_get_thread_num();
        int nth = omp_get_num_threads();

        int my_begin = tid * N / nth;
        int my_end = my_begin + N / nth;

        int i;
        //#pragma omp for schedule(static, 8)
        for (i = my_begin; i < my_end; i++) {
            myres += cos(i * step + step_half);
        }
        #pragma omp atomic
        res += myres;
    }
    
    res *= step;
    double end = gettime();

    double analytic = sin(b);
    printf("%16.18f\t", fabs(analytic - res));
    printf("%f\n", end - start);

    return 0;
    //gcc -O3 -fopenmp -o numint_p numint_p.c -lm
    //OMP_NUM_THREADS=1000 ./numint
}