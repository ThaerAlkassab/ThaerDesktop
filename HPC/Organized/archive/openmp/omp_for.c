#include <stdio.h>
#include <omp.h>

#define N 100

int main( int argc, char ** argv )
{
    int i;
    int values[N];
    
    #pragma omp parallel for private(i) schedule(static,8) ordered
    for( i = 0; i < N; i++ )
    {
        values[i] = omp_get_thread_num();
        #pragma omp ordered
        printf("%d",values[i]);
    }

//    for( i = 0; i < N; i++ )
//        printf("%d",values[i]);
    printf("\n");
    return 0;
}
