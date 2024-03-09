#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[])
{
    int numtasks, rank, dest, source, rc, count, tag=1;
    char inmsg, outmsg='x';
    MPI_Status Stat;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(rank==0){
        dest = 1;
        source = 1;
        printf("I am R%d sending %c to rank %d\n",
                rank, outmsg, dest);
        rc = MPI_Send(&outmsg, 1, MPI_CHAR,
                       dest, tag, MPI_COMM_WORLD);
        printf("R%d: data sent, waiting on reply\n", rank);
        rc = MPI_Recv(&inmsg, 1, MPI_CHAR,
                       source, tag, MPI_COMM_WORLD, &Stat);
        // MPI_Sendrecv ... ?
        printf("R%d received %c from %d\n", rank, inmsg, source);
    }
    else if(rank==1){
        dest = 0;
        source = 0;
        printf("I am R%d, waiting for data from %d\n", rank, source);
        rc = MPI_Recv(&inmsg, 1, MPI_CHAR,
                       source, tag, MPI_COMM_WORLD, &Stat);
        printf("R%d: Received %c, sending %c to %d\n",
               rank, inmsg, outmsg, dest);
        rc = MPI_Send(&outmsg, 1, MPI_CHAR,
                      dest, tag, MPI_COMM_WORLD);
        // MPI_Sendrecv .... ?
        printf("R%d: Data sent.\n", rank);
    }
    MPI_Finalize();
    return 0;
}

// Homework: Implement with MPI_Sendrecv