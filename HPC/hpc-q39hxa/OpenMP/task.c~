#include <stdio.h>
#include <omp.h>

int main()
{
    printf("a ");
    #pragma omp parallel
    #pragma omp single
    {
        #pragma omp task
        printf("");
        #pragma omp task
        printf("car ");
        #pragma omp task
        printf("race ");
    }
    printf("is fun ");
    printf("to watch ");
    printf("\n");
    return 0;
}
