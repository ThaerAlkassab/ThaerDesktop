#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char ** argv)
{
    int rank, size;
    MPI_Status Stat;
    MPI_Init( & argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

   if( rank != 0 )
   {
       printf("Master called with nonzero rank.\n");
       MPI_Abort( MPI_COMM_WORLD, -1 );
   }
    
        srand( time( NULL ) );
        int gen = rand() % 100 + 1;
        int inp = -1;
        int rep;
        int c = 0;
        
        printf("R0: I have thought of a number between 1 and 100.\n");
        while( inp != gen )
        {
            printf("R0: Give me your guess!\n");
//            MPI_Recv( &inp, 1, MPI_INT,
//                      1, 0, MPI_COMM_WORLD, &Stat );
            MPI_Bcast( &inp, 1, MPI_INT, c % (size-1) + 1, MPI_COMM_WORLD);
            c++;
            if( inp > gen )
            {
                printf("R0: Your guess is too big!\n");
                rep = 1;
            }
            else if( inp < gen )
            {
                printf("R0: Your guess is too small!\n");
                rep = -1;
            }
            else
                rep = 0;
//            MPI_Send( &rep, 1, MPI_INT,
//                1, 0, MPI_COMM_WORLD );
            MPI_Bcast( &rep, 1, MPI_INT, 0, MPI_COMM_WORLD );
        }
//        printf("R0: You guessed the number! You needed %d guesses.\n", c);
        printf("R0: Rank %d has guessed the number in %d guesses!\n", (c-1)%(size-1)+1, c );

    MPI_Finalize();
    return 0;
}
