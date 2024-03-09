#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main( int argc, char ** argv )
{
    int n = atoi( argv[1] );
    int k = 0;
    int i;
    
    srand48(time(NULL));
    
    for( i = 0; i < n; i ++ )
    {
        double x = drand48();
        double y = drand48();
        if( x*x + y*y < 1 )
            k++;
    }
    
    double pi = 4.*k/n;
    printf("Result: %18.16le\n", pi );
    printf("Error: %18.16le\n", pi-M_PI );
    
    return 0;
}
