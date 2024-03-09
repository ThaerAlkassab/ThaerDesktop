#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main( int argc, char ** argv )
{
    int k = 0;
    int n = atoi( argv[1] );
    int i;
    
    if( argc == 2 )
        srand(time(NULL));
    else
        srand(atoi(argv[2]));
    
    for( i = 0; i < n; i++ )
    {
        double x = (double)rand() / (double)RAND_MAX;
        double y = (double)rand() / (double)RAND_MAX;
        if( x*x + y*y <= 1 )
        {
            k++;
        }
    }
    double result = 4.0*k/n;
    printf("Result: %.16f\n",result);
    printf("Error: %.16f\n",result - M_PI);
    return 0;
}
