#include <stdio.h>
#include <mpi.h>

int main( int argc, char ** argv )
{
    int myrank, ranks;
    int number[2];
    
    MPI_Init( & argc, & argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
    MPI_Comm_size( MPI_COMM_WORLD, &ranks );
    
    if( myrank == 0 )
    {
        scanf("%d", number);
        scanf("%d", number+1);
    }
    
    MPI_Datatype numbertype;
    MPI_Type_contiguous(2, MPI_INT, &numbertype);
    MPI_Type_commit( &numbertype );
    
    MPI_Bcast( number, 1, numbertype, 0, MPI_COMM_WORLD );
    printf("Got %d and %d at %d from %d\n", number[0], number[1], myrank, ranks);

    MPI_Type_free(&numbertype);    
    MPI_Finalize();
    return 0;
}
