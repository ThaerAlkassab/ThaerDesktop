#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, num_processes;
    int guess, response;
    MPI_Status status;
    srand(time(NULL));
    int secret_number = rand() % 100 + 1;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    if (rank == 0) {



        printf("R0: I have thought of a number between 1 and 100.\n");
        int num_guesses = 0; // Track number of guesses for rank 0

        while (true) {
            guess = rand() % 100 + 1; // Generate guess
            MPI_Send(&guess, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); // Send guess to rank 1

            MPI_Recv(&response, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &status); // Receive response from rank 1

            num_guesses++; // Increment guesses

            if (response == 0) {
                printf("R0: You guessed the number %d! It took %d guesses.\n",secret_number, num_guesses);
                break; // Exit loop and program
            } else if (response > 0) {
                printf("R0: Your guess is %d and its too big !\n",guess);
            } else {
                printf("R0: Your guess is %d and its  too small!\n",guess);
            }
        }
    } else if (rank == 1) {
        int min = 1, max = 100;

          while (true) {
            MPI_Recv(&guess, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status); // Receive guess from rank 0
            if (guess == 0) {
                break; // Exit loop and program if guessed correctly
            } else if (guess > secret_number) {
                response = 1; // Guess is too big
            } else if (guess < secret_number) {
                response = -1; // Guess is too small
            } else {
                response = 0; // Guessed correctly
            }
            MPI_Send(&response, 1, MPI_INT, 0, 1, MPI_COMM_WORLD); // Send response to rank 0
        }
    }

    MPI_Finalize();
    return 0;
}