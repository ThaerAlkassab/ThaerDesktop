#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <mpi.h>

typedef unsigned long long int myInt;
typedef double myFloat;
#define MY_MPI_FLOAT_TYPE MPI_FLOAT

double gettime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + 0.000001 * tv.tv_usec;
}

void printMatix(myInt N, myFloat* data) {
    myInt i, j;
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            printf("%.6f \t", data[i*N + j]);
        }
        printf("\n");
    }
}

void print_diags(myInt N, myFloat* data, myInt s_start, myInt s_end, int rank) {
    myFloat mdsum = 0;
    myFloat rdsum = 0;

    myInt i;
    for(i = s_start; i < s_end; i++) {
        mdsum += data[(i-s_start) * N + i];
        rdsum += data[(i-s_start) * N + N - 1 - i];
    }
    if (rank == 0) {
        MPI_Reduce(MPI_IN_PLACE, &mdsum, 1, MY_MPI_FLOAT_TYPE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(MPI_IN_PLACE, &mdsum, 1, MY_MPI_FLOAT_TYPE, MPI_SUM, 0, MPI_COMM_WORLD);

        printf("Main diagonal: %.6f \n", mdsum);
        printf("Reverse diagonal: %.6f \n", rdsum);
    } else {
        MPI_Reduce(&mdsum, NULL, 1, MY_MPI_FLOAT_TYPE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(&rdsum, NULL, 1, MY_MPI_FLOAT_TYPE, MPI_SUM, 0, MPI_COMM_WORLD);
    }
}

void transpose(myInt N, myFloat* data) {

}

int main(int argc, char ** argv) {
    srand(0);

    //Serial
    int ranks, rank, error_code;
    myInt N = atoi(argv[1]);
    myFloat* data = (myFloat*) malloc(N*N*sizeof(myFloat));

    //Parallel
    error_code = MPI_Init(&argc, &argv);
    if (error_code != MPI_SUCCESS) {
        printf("Error initializing MPI enviroment.\n");
        MPI_Abort(MPI_COMM_WORLD, error_code);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &ranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //get the border
    myInt rem = (N*N) % ranks;
    myInt s_split = (N*N) / ranks;
    myInt s_start = s_split * rank;
    myInt s_end = s_start + s_split;
    if (rank < rem) {
        s_start += rank;
        s_end += rank + 1;
    } else {
        s_start += rem;
        s_end += rem;
    }
    printf("P%d: managing %d to %d\n", rank, s_start, s_end);
    MPI_Barrier(MPI_COMM_WORLD);

    myInt i;
    for(i = s_start; i < s_end; i++) {
        data[i] = rand() / (myFloat)RAND_MAX;
    }

    if (rank == 0) {
        printf("%.5f\n", data[N*N-1]); //memory protection, not see the other data
    }

    print_diags(N, data, s_start, s_end, rank);

    
    //
    if (rank == 99) {
        double a = log(12.34) / log(sqrt(3));
        double start = gettime();
        printMatix(N, data);
        double end = gettime();
        printf("%16.18f \n", end-start);
    }
    

    MPI_Finalize();
    free(data);
    return 0;
}

//module list
//module avail
//module add mpi/openmpi-x86_64
//mpicc -O3 -lm -Wall -o mpi mpi.c
//mpirun -n 4 mpi
//mpirun --map-by core -n 4 ./mpi