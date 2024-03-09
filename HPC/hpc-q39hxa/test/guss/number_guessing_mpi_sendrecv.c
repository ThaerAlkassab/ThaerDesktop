#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int min0, max0;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    srand( time( NULL ) );

    if (size != 2) {
        if (rank == 0) {
            printf("This program requires exactly 2 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }
    guss0 = (rand() % 100) + 1;
    min0 = 1;
    max0 = 100;

    if (rank == 0) {
        int secretNumber = guss0;
        int guess;
        printf("R0: I've chosen a number between 1 and 100. Start guessing!\n");

        do {
            MPI_Sendrecv(&secretNumber, 1, MPI_INT, 1, 0, &guess, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
            printf("R0: Received guess from R1: %d\n", guess);
            if (guess == secretNumber) {
                printf("R0: Correct guess! You got it.\n");
            } else if (guess < secretNumber) {
                printf("R0: Your guess is too small! Try again.\n");
                min0 = guess + 1;
            } else {
                printf("R0: Your guess is too large! Try again.\n");
                max0 = guess -1;
            }
        } while (guess != secretNumber);
    } else { 
        int secretNumber;
        int guess = -1;

        MPI_Sendrecv(&guess, 1, MPI_INT, 0, 0, &secretNumber, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        do {
            
            guess = (rand() % max0 + min0;
            printf("R1: I am guessing %d.\n", guess);
            MPI_Sendrecv(&guess, 1, MPI_INT, 0, 0, &secretNumber, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        } while (guess != secretNumber);
    }

    MPI_Finalize();
    return 0;
}
