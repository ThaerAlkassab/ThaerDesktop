#include <mpi.h>
#include <stdio.h>
#include <sched.h>

int main( int argc, char ** argv )
{
    int ranks, myrank, error_code, namelength, cpu;
    char name[MPI_MAX_PROCESSOR_NAME];
    
    error_code = MPI_Init( & argc, &argv );
    if( error_code != MPI_SUCCESS )
    {
        printf("Error initializing MPI environment\n");
        MPI_Abort( MPI_COMM_WORLD, error_code );
    }
    MPI_Comm_size( MPI_COMM_WORLD, &ranks );
    MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
    MPI_Get_processor_name( name,  &namelength );
    cpu = sched_getcpu();
    printf("I am %s rank #%d on CPU#%d of %d.\n", name, myrank, cpu, ranks );
    
    MPI_Finalize();
    return 0;
}
