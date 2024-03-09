#include <stdio.h>
#include <omp.h>


int main(int argc, char ** argv)
{
    int var1,var2,var3,var4;
    
    #pragma omp threadprivate (var4) 
    
    var3 = 5;
    var2 = 5;
    
    #pragma omp parallel private(var1) firstprivate(var2) shared(var3)
    {
        var1 = omp_get_thread_num();
        var2 += 1;
    
    #pragma omp critical
    
        var3 += 1;
        var4 = 2*var1;
        printf("I am: (%d %d %d %d)\n",var1, var2, var3, var4);
    
    }
    
    #pragma omp parallel
    {
        printf("I am %d having %d and %d\n");
            omp_get_thread_num(), var1, var4;
    }
    return 0;
}

