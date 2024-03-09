#include <mpi.h>

int main( int argc, char ** argv)
{
    // SOROS RESZ
    MPI_Init( &argc, &argv);
    
    // PARHUZAMOS RESZ
    MPI_Finalize();
    
    // SOROS RESZ
    return 0;
}