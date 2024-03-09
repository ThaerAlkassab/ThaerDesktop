#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef IS_PARALLEL
	#include <omp.h>
#endif

double gettime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + 0.000001 * tv.tv_usec;
}

double randInRange() {
    return rand() / ((double) RAND_MAX);
}

int main(int argc, char * argv[]) {
    int rnd = 0;

    double analytic = M_PI;
    double res = 0;
	unsigned int n = 10;
    // Reading in data from command line
    if (argc > 1) {
        n = (int) atoll(argv[1]);
    }
    if (argc > 2) {
        rnd = (int) atoi(argv[2]);
    } else {
        rnd = time(0);
    }
    srand(rnd);


	// Timer start
    double start = gettime();

	#ifdef IS_SERIAL
        int k = 0;
        int i = 0;
		for (i = 0; i < n; i++) {
            double x = randInRange();
            double y = randInRange();
            double dist = x*x + y*y;
			if (dist <= 1) {
                k++;
            }
		}
        res = (double)k / (double)n * 4.0;
        printf("%f\n", res);
        printf("%f\n", fabs(analytic-res));
	#endif
	
	#ifdef IS_PARALLEL
        int k = 0;
        int i = 0;
        #pragma omp parallel firstprivate(rnd)
        {
            rnd += omp_get_thread_num(); 
            #pragma omp for schedule(static) reduction(+:k) private(i)
            for (i = 0; i < n; i++) {
                double x = rand_r(&rnd) / ((double) RAND_MAX);
                double y = rand_r(&rnd) / ((double) RAND_MAX);
                double dist = x*x + y*y;
                if (dist <= 1) {
                    k++;
                }
            }
        }
        
        res = (double)k / (double)n * 4.0;
        printf("%.17f\n", res);
        printf("%.17f\n", fabs(analytic-res));
	#endif

	// Timer end
    double end = gettime();
    printf("%.17f\n", end - start);

    return 0;
}

//gcc -O3 -lm -Wall -o pi_s pi.c -D IS_SERIAL
//gcc -O3 -fopenmp -lm -Wall -o pi_p pi.c -D IS_PARALLEL
//OMP_NUM_THREADS=1000 ./pi_p