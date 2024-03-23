#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int can_put(int * queens, int N, int row, int col) {
    int i;
    for (i = 0; i < row; i++) {
        int s = queens[i];
        if (s == col) {
            return 0;
        } else if ((row - i)  == abs(s - col)) {
            return 0;
        }
    }
    return 1;
}

int count_queens(int * queens, int N, int row) {
    if (row == N) {
        return 1;
    }
    int sum = 0;
    int i;
    for (i = 0; i < N; i++) {
        if (can_put(queens, N, row, i) == 1) {
            queens[row] = i;
            sum += count_queens(queens, N, row+1);
        }
    }
    return sum;
}

int main(int argc, char ** argv) {
    //board size
    int N = atoi(argv[1]);
    
    

    //Count solution
    double start_time, end_time;
    int solutions = 0;
    
    

    start_time = omp_get_wtime();

    //estimate iteration
    int max_iter = N;
    if (N % 2 == 0) {
        max_iter = N / 2;
    }

    int i;
    #pragma omp parallel for
    for (i = 0; i < max_iter; i++) {
        int * queens = calloc(N, sizeof(int));
        queens[0] = i;
        #pragma omp atomic
		solutions += count_queens(queens, N, 1);

        free(queens);
    }

    if (N % 2 == 0) {
        solutions *= 2;
    }
    end_time = omp_get_wtime();

    //print result
    printf("The execution time is %f\n", end_time - start_time);
    printf("combination found: %d \n", solutions);
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