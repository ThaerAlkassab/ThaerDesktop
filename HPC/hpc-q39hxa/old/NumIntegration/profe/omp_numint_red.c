#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>

double gettime()
{
    return omp_get_wtime();
}

int main( int argc, char ** argv )
{
    typedef double myf;
    #define mycos(x) cos(x)
    // cosf: float, cos: double, cosl: long double
    typedef int myi;
    myf a = 0; // float, double, long double // not change
    myf b = 1.570796326794896619231321691639751442L; // not change
    myi N = (myi)atoll(argv[1]); // not change
    myf res = 0; //change
    myf dx = (b-a)/N; // not change
    myf dxhalf = dx*0.5; // no change

    myi i;
    // loop over subintervals
    double start = gettime();
    #pragma omp parallel for private(i) schedule(runtime) reduction(+:res)
    {
        //myi i;
        //myf myres = 0;
        /*int tid = omp_get_thread_num();
        int nth = omp_get_num_threads();
        myi my_begin = tid * N / nth;
        myi my_end = my_begin + N / nth;*/
        //#pragma omp for schedule(static) reduction(+:res)
        for(i=0;i<N;i++)
        {
           // myres += mycos( i*dx + dxhalf );
           res += mycos(i*dx + dxhalf);
        }
        //#pragma omp atomic
        //res += myres;
    }
    res *= dx;
    double end = gettime();

//    # print results
    printf("Results: %18.16Lf\n", (long double)res);
//    # compare with analytic result (1)
    printf("Error: %18.16Lf\n", (long double)(res - 1.0));
    printf("Time: %8.6f\n", end - start);
    return 0;
}
