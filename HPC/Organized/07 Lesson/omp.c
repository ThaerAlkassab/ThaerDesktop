#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char ** argv) {
    printf("a ");
    #pragma omp parallel sections
    {
        #pragma omp section
        printf("car ");
        #pragma omp section
        printf("race ");
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