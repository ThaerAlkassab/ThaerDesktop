#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char ** argv)
{
    int rank;
    MPI_Status Stat;
    MPI_Init( & argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

    if(rank == 0)
    {
        srand( time( NULL ) );
        int gen = rand() % 100 + 1;
        int inp = -1;
        int rep;
        int c = 0;

        printf("R0: I have thought of a number between 1 and 100.\n");
        while( inp != gen )
        {
            printf("R0: Give me your guess!\n");
            MPI_Recv( &inp, 1, MPI_INT,
                      1, 0, MPI_COMM_WORLD, &Stat );
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
            MPI_Send( &rep, 1, MPI_INT,
                1, 0, MPI_COMM_WORLD );
        }
        printf("R0: You guessed the number! You needed %d guesses.\n", c);
    }
    else if(rank == 1)
    {
        int rep = 1;
        int min = 1;
        int max = 100;
        while( rep != 0 )
        {
            int guess = ( 2*min + max ) / 3;
            printf("R1: I am guessing %d.\n", guess);
            MPI_Send( &guess, 1, MPI_INT,
                      0, 0, MPI_COMM_WORLD );
            MPI_Recv( &rep, 1, MPI_INT,
                      0, 0, MPI_COMM_WORLD, &Stat );
            if( rep > 0 )
                max = guess - 1;
            else if ( rep < 0 )
                min = guess + 1;
        }
    }
    MPI_Finalize();
    return 0;
}
