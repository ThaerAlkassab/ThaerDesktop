#include <stdio.h>
#include <mpi.h>

int main( int argc, char ** argv )
{
    int ranks, myrank, error_code;
    error_code = MPI_Init( &argc, &argv );
    if(error_code != MPI_SUCCESS)
    {
        printf("Erorr initializing MPI environment.\n");
        MPI_Abort(MPI_COMM_WORLD, error_code);
    }
    
    MPI_Comm_size(MPI_COMM_WORLD, &ranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    printf("I am rank #%d of %d.\n", myrank, ranks);
    
    MPI_Finalize();
    return 0;
}