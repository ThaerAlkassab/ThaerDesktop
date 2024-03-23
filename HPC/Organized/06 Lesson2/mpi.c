#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char ** argv) {
    srand(0);

    //Serial
    int myrank, ranks, error_code;
    int number[2];

    //Parallel
    error_code = MPI_Init(&argc, &argv);
    if (error_code != MPI_SUCCESS) {
        printf("Error initializing MPI enviroment.\n");
        MPI_Abort(MPI_COMM_WORLD, error_code);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &ranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if (myrank == 0) {
        scanf("%d", number);
        scanf("%d", number+1);
    }

    MPI_Datatype numberType;
    MPI_Type_contiguous(2, MPI_INT, &numberType);
    MPI_Type_commit(&numberType);

    MPI_Bcast(number, 1, numberType, 0, MPI_COMM_WORLD);
    printf("R%d: %d %d \n", myrank, number[0], number[1]);

    MPI_Type_free(&numberType);
    MPI_Finalize();
    return 0;
}

//module list
//module avail
//module add mpi/openmpi-x86_64
//mpicc -O3 -lm -Wall -o mpi mpi.c
//mpirun -n 4 mpi
//mpirun --map-by core -n 4 ./mpi

//   rm -f /dev/shm/*