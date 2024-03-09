#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

typedef long double myf;

double get_time(){
    return omp_get_wtime();
}


int main(int argc, char ** argv)
{
    int n = (int)atoll(argv[1]); // number of intervals (myi)atoll(argv[1])
    int k = 0;
    int i;
    
    myf x;
    myf y;
    
    unsigned int seed;

    seed = (time(NULL));
    
    double start = get_time();
    
    #pragma omp parallel firstprivate(seed)
    {
        seed += omp_get_thread_(num);
        #pragma omp parallel for private(i,x,y) reduction(+:k)
        for (i = 0; i < n; i++) {
            x = rand_r(&seed) / ((double) RAND_MAX);
            y = rand_r(&seed) / ((double) RAND_MAX);
            if (x*x + y*y <= 1){k++;}
        }
    }
    double end = get_time();
    
    printf("Result: %18.16Lf\n",(long double) 4*k/n);
    printf("Error: %18.16Lf\n",(long double) 4*k/n - M_PI);
    printf("Time: %8.6f\n", end - start);

    return 0;
}