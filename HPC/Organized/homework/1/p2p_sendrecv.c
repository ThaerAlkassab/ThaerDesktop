#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char ** argv) {

    //Serial
    int error_code, numtasks, rank, dest, source, tag=1;
    char inmsg, outmsg='x';
    MPI_Status Stat;

    error_code = MPI_Init(&argc, &argv);
    //Parallel
    if (error_code != MPI_SUCCESS) {
        printf("Error initializing MPI enviroment.\n");
        MPI_Abort(MPI_COMM_WORLD, error_code);
    }

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        dest = 1;
        source = 1;
        printf("R%d: sending %c to rank %d\n", rank, outmsg, dest);
        MPI_Sendrecv(&outmsg, 1, MPI_CHAR, dest, tag, &inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);

        printf("R%d: received %c from %d \n", rank, inmsg, source);


    } else if (rank == 1) {
        dest = 0;
        source = 0;
        printf("R%d: waiting data from %d...\n", rank, source);
        printf("R%d: sending %c from %d \n", rank, outmsg, dest);
        MPI_Sendrecv(&outmsg, 1, MPI_CHAR, dest, tag, &inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);

        
        //MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        printf("R%d: data sent\n", rank);
    } 

    MPI_Finalize();

    //Serial
    return 0;
}

//module list
//module avail
//module add mpi/openmpi-x86_64
//mpicc -O3 -lm -Wall -o p2p_sendrecv p2p_sendrecv.c
//mpirun -n 2 p2p_sendrecv
//mpirun --map-by core -n 2 ./p2p_sendrecv