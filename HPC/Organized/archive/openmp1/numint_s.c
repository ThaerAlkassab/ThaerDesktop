#include <stdio.h>
#include <math.h>
#include <sys/time.h>

double gettime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + 0.000001 * tv.tv_usec;
}

int main(int argc, char ** argv) {
    double a = 0;
    double b = M_PI / 2;
    double N = (double)atoll(argv[1]);
	//double N = 0.0;
	//scanf("%lf", &N);

	//trapezoid formula
    double step = (b - a) / N;
    double step_half = step / 2;
    double res = 0;

    double start = gettime();
    double i = 0;
    for (i=0; i < N; i++) {
        res += cos((i * step + (i * step + step)) / 2);
    }
    res *= step;
	double end = gettime();
    
    double analytic = sin(b);
    printf("%16.18f\t", fabs(analytic-res));
	printf("%f\n", end-start);
    
    return 0;
}