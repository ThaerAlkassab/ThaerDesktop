#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("a ");
            #pragma omp task
            printf("");
            #pragma omp task
            printf("car ");
            #pragma omp task
            printf("race ");

            #pragma omp taskwait

            printf("is fun ");
            printf("to watch ");
        }
    }
    printf("\n");
    return 0;
}
