#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char ** argv) {
    //Serial
    srand(time(0));
    int error_code, ranks, rank, other, tag=1, msg;
    MPI_Status Stat;

    error_code = MPI_Init(&argc, &argv);
    //Parallel
    if (error_code != MPI_SUCCESS) {
        printf("Error initializing MPI enviroment.\n");
        MPI_Abort(MPI_COMM_WORLD, error_code);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &ranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (rank == 0) {
        other = 1;
        int answear = rand() % 100 + 1;
        int guess = -1;
        int c = 0;
        printf("R%d: guessed number %d \n", rank, answear);

        while(guess != answear) {
            int src = c % (ranks-1) + 1;
            MPI_Bcast(&msg, 1, MPI_INT, src, MPI_COMM_WORLD);
            printf("R%d: received %d from %d \n", rank, msg, other);
            c++;
            guess = msg;
            if (guess < answear) {
                msg = 1;
                printf("R%d: sending need higher...\n", rank);
                MPI_Send(&msg, 1, MPI_INT, other, tag, MPI_COMM_WORLD);
            } else if (guess > answear) {
                msg = -1;
                printf("R%d: sending need lower...\n", rank);
                MPI_Send(&msg, 1, MPI_INT, other, tag, MPI_COMM_WORLD);
            }
            MPI_Bcast(&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);
        }
        msg = 0;
        printf("R%d: %d guessed the number number from %d guesses.\n", rank, (c-1) % (ranks-1) + 1, c);
        MPI_Bcast(&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);


    } else {
        other = 0;
        msg = -1;
        int tries = 0;
        int up = 101;
        int down = 0;
        int guess = 0;
        int c = 0;

        while(msg != 0) {
            //guess = (up + down) / 2;
            if (c % (ranks-1) + 1 == rank) {
                guess = rand() % (up - down + 1) + down;
                printf("R%d: sending %d as guess\n", rank, guess);
                MPI_Bcast(&guess, 1, MPI_INT, rank, MPI_COMM_WORLD);
            } else {
                MPI_Bcast(&guess, 1, MPI_INT, c % (ranks-1) + 1, MPI_COMM_WORLD);
            }
            
            MPI_Bcast(&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);
            tries++;
            if (msg == 1) {
                down = guess;
            } else if (msg == -1) {
                up = guess;
            }
            c++;
        }
        printf("R%d: number is %d in %d tries\n", rank, guess, tries);
    } 

    MPI_Finalize();
    //Serial
    return 0;
}

//module list
//module avail
//module add mpi/openmpi-x86_64
//mpicc -O3 -lm -Wall -o mpi mpi.c
//mpirun -n 4 mpi
//mpirun --map-by core -n 4 ./mpi
//mpirun -n 1 master : -n 1 slave1 : -n 1 slave2