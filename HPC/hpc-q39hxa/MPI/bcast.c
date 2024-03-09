#include <mpi.h>
#include <stdio.h>

int main( int argc, char ** argv )
{
    int myrank, ranks;
    int number;
    
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
    MPI_Comm_size( MPI_COMM_WORLD, &ranks );
    
    if( myrank == 0 )
        scanf("%d", &number);
        
    MPI_Bcast( &number, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Got %d at %d/%d\n", number, myrank, ranks);
    
    MPI_Finalize();
    return 0;
}
