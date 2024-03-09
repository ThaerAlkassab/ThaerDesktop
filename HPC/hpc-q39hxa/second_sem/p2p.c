#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main ( int argc, char *argv[] )
{
    int numtaskes, rank, dest, source, rc, count, tag=1;
    char inmsg, outmsg='x';
    MPI_Status State;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtaskes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0)
    {
        dest = 1;
        source = 1;
        printf ("I am R%d sending %c to rank %d\n", rank, outmsg, dest);
        rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        printf ("R%d: data sent, waiting on replay\n", rank);
        rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &State);
        printf ("R%d: %c recived from %d\n", rank, inmsg, source);   
    }
    
    else if (rank == 1)
    {
        dest = 0;
        source = 0;
        printf ("I am R%d sending %c to rank %d\n", rank, outmsg, dest);
        rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        printf ("R%d: %c recived from %d\n", rank, inmsg, source);
        rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &State);
        printf ("R%d: data sent, waiting on replay\n", rank);
    }
    
    MPI_Finalize();
    return 0;
}