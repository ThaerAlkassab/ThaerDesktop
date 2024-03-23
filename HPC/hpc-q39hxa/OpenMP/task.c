#include <stdio.h>
#include <omp.h>

int main(int argc, char ** argv)
{
    int n = atoi(argv[1]);
    printf("a ");
    #pragma omp parallel
    #pragma omp single
    {
        int i;
        #pragma omp task
        printf("");
        for(i = 0; i < n; i++ )
            #pragma omp task
            printf("car ");
        for(i = 0; i < n; i++ )
            #pragma omp task
            printf("race ");
    }
    printf("is fun ");
    printf("to watch ");
    printf("\n");
    return 0;
}
