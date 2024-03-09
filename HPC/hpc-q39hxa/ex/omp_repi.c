#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main( int argc, char ** argv )
{
    int k = 0;
    int n = atoi( argv[1] );
    int i;
    unsigned int seed;
    
    if( argc == 2 )
        seed = time(NULL);
    else
        seed = atoi(argv[2]);
    
    #pragma omp parallel firstprivate( seed )
    {
        seed += 119*omp_get_thread_num();
        
        #pragma omp for reduction(+:k) private(i)
        for( i = 0; i < n; i++ )
        {
            double x = (double)rand_r(&seed) / (double)RAND_MAX;
            double y = (double)rand_r(&seed) / (double)RAND_MAX;
            if( x*x + y*y <= 1 )
                k++;
        }
    }
    double result = 4.0*k/n;
    printf("Result: %.16f\n",result);
    printf("Error: %.16f\n",result - M_PI);
    return 0;
}
