#include <stdio.h>
#include <omp.h>

#define N 100

int main( int argc, char ** argv )
{
    int i;
    char values[N+1];
    values[N]='\0';
    
    #pragma omp parallel private(i)
    {
        #pragma omp for schedule(runtime)
        for( i = 0; i < N; i++ )
            values[i] = '0'+omp_get_thread_num();
    }

    printf("%s", values);
    printf("\n");
    return 0;
}
