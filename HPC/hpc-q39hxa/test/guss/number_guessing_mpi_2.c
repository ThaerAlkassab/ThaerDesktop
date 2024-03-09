#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char ** argv)
{
    int rank, size;
    MPI_Status Stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
    {
        srand(time(NULL));
        int gen = rand() % 100 + 1;
        printf("R0: I have thought of a number between 1 and 100.\n");

        MPI_Bcast(&gen, 1, MPI_INT, 0, MPI_COMM_WORLD);

        int inp = -1;
        int rep;
        int c = 0;

        while(inp != gen)
        {
            printf("R0: Give me your guess!\n");
            MPI_Recv(&inp, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &Stat);
            c++;
            if(inp > gen)
            {
                printf("R0: Your guess is too big!\n");
                rep = 1;
            }
            else if(inp < gen)
            {
                printf("R0: Your guess is too small!\n");
                rep = -1;
            }
            else
                rep = 0;
            MPI_Send(&rep, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        }
        printf("R0: You guessed the number! You needed %d guesses.\n", c);
    }
    else
    {
        int rep = 1;
        int min = 1;
        int max = 100;
        int guess = min + (max - min) / 2; // Initial guess at midpoint

        while(rep != 0)
        {
            printf("R1: I am guessing %d.\n", guess);
            MPI_Send(&guess, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Recv(&rep, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &Stat);
            if(rep > 0)
                max = guess - 1; // Adjusting upper bound
            else if (rep < 0)
                min = guess + 1; // Adjusting lower bound
            guess = min + (max - min) / 2; // Update guess
        }
    }
    MPI_Finalize();
    return 0;
}
