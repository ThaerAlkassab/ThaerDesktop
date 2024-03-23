#include <stdio.h>
#include <omp.h>

int main( int argc, char ** argv )
{
    int var3; // shared by default
    
    var3 = 5;
    
    #pragma omp parallel
    {
        int var1 = omp_get_thread_num(); // private by default
        int var2 = omp_get_num_threads();
        printf("I am thread %d of %d (shared %d)\n", var1, var2, var3);
    }
    return 0;
}
