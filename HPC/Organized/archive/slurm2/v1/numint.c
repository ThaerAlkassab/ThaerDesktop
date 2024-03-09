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

    double step = (b - a) / N;
    double step_half = step / 2;
    double res = 0;
    
    double i = 0;
    
    for (i=1; i < N; i++) {
        res += cos(i * step);
    }
    res = res * 2;
    res += cos(a) + cos(b);
    res *= step_half;
    
    printf("%16.18f \n", res);
    
    return 0;
}
