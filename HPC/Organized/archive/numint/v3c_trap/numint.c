#include <stdio.h>
#include <math.h>
#include <sys/time.h>


double gettime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL); // both are output arguments. we do not need time zone -> it is NULL
    return tv.tv_sec + 0.000001 * tv.tv_usec;
}

int main( int argc, char ** argv )
{
    typedef double myf;
    #define mycos(x) cos(x)
    // cosf: float, cos: double, cosl: long double
    typedef int myi;
    myf a = 0; // float, double, long double
    myf b = 1.570796326794896619231321691639751442L;
    myi N = (myi)atoll(argv[1]);
    myf res = 0;
    myf dx = (b-a)/N;
    myf dxhalf = dx*0.5;
    myi i;

    // loop over subintervals
    double start = gettime();
    for(i=1;i<N;i++)
    {
        res += mycos( i*dx );
    }
    res *= 2.0;
    res += mycos(a) + mycos(b);
    res *= dxhalf;
    double end = gettime();

//    # print results
    printf("Results: %18.16Lf\n", (long double)res);
//    # compare with analytic result (1)
    printf("Error: %18.16Lf\n", (long double)(res - 1.0));
    printf("Time: %8.6f\n", end - start);
    return 0;
}
