#include <sched.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char ** argv) {

    //Serial
    int ranks, myrank, error_code, number;

    error_code = MPI_Init(&argc, &argv);
    //Parallel
    if (error_code != MPI_SUCCESS) {
        printf("Error initializing MPI enviroment.\n");
        MPI_Abort(MPI_COMM_WORLD, error_code);
    }

    MPI_Comm_size(MPI_COMM_WORLD, &ranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if (myrank == 0) {
        scanf("%d", &number);
    }

    MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Got %d az %d/%d\n", number, myrank, ranks);

    MPI_Finalize();
    //Serial
    return 0;
}

//module list
//module avail
//module add mpi/openmpi-x86_64
//mpicc -O3 -lm -Wall -o mpi mpi.c
//mpirun -n 4 mpi
//mpirun --map-by core -n 4 ./mpi