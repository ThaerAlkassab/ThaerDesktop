#include <stdio.h>
#include <omp.h>

#define N 100

int main(int argc, char ** argv) {
    int i;
    int values[N];

    #pragma omp parallel for private(i) schedule(static, 8) ordered
    for (i = 0; i < N; i++) {
        values[i] = 2 * i - 1;
        #pragma omp ordered
        printf("%d;", values[i]);
    }
    printf("\n");

    int sum = 0;
    #pragma omp parallel for private(i) schedule(static, 8) reduction(+:sum)
    for (i = 0; i < N; i++) {
        sum += values[i];
    }
    printf("%d\n", sum);

    int max = 0;
    #pragma omp parallel private(i)
    {
        int mymax = 0;
        #pragma omp for
        for (i = 0; i < N; i++) {
            if(values[i] > mymax) {
                mymax = values[i];
            }
        }
        #pragma omp critical
        if (max < mymax) {
            max = mymax;
        }
    }
    printf("%d\n", max);


    return 0;

    //gcc -O3 -lm -fopenmp -o omp_for omp_for.c
    //OMP_NUM_THREADS=8 ./omp_for
}

