#include <stdio.h>
#include <omp.h>

int main( int argc, char ** argv )
{
    static int var1, var2, var3, var4;
    #pragma omp threadprivate( var4 )
    
    var3 = 5; var2 = 5;
    
    #pragma omp parallel private(var1) firstprivate(var2) shared(var3)
    {
        var1 = omp_get_thread_num();
        var2 += 1;
        #pragma omp atomic
        var3 += 1;
        #pragma omp barrier
        var4 = 2*var1;
        printf("My numbers are: %d, %d, %d, %d\n", var1, var2, var3, var4);
    }
    
    #pragma omp parallel
    printf("I am %d, having %d, %d, %d and %d.\n",
        omp_get_thread_num(), var1, var2, var3, var4 );
    return 0;
}
