#include <stdio.h>
#include <omp.h>

int main()
{
    printf("a ");
    #pragma omp parallel sections
    {
        #pragma omp section
        printf("car ");
        #pragma omp section
        printf("race ");
    }
    printf("is fun ");
    printf("to watch ");
    printf("\n");
    return 0;
}
