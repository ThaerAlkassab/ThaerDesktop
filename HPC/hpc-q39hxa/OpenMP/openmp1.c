#include <stdio.h>
#include <omp.h>

int main(int argc, char ** argv)
{
    int var1,var2,var3;
    var3 = 5;
    
    #pragma omp parallel private(var1, var2) shared(var3)
    {
        var1 = omp_get_thread_num();
        var2 = omp_get_num_threads();
        printf("I am thead %d of %d (shared %d)\n",var1, var2, var3);
    }
    return 0;
}

