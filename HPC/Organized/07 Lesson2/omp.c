#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char ** argv) {
    int n = atoi(argv[1]);
    printf("a ");
    #pragma omp parallel
    #pragma omp single
    {
        int i;
        #pragma omp task
        printf("");
        for (i = 0; i < n; i++) {
            #pragma omp task
            printf("car ");
        }
        for (i = 0; i < n; i++) {
            #pragma omp task
            printf("race ");
        }
        
    }
    printf("is fun to watch \n");
    return 0;
}

//module list
//module avail
//module add mpi/openmpi-x86_64
//mpicc -O3 -lm -Wall -o mpi mpi.c
//mpirun -n 2 mpi 4
//mpirun --map-by core -n 4 ./mpi
//gcc -O3 -lm -Wall -fopenmp -o omp omp.c
//   rm -f /dev/shm/*
// OMP_NUM_THREADS=4 ./omp