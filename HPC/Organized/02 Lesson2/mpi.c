#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char ** argv) {
    //Serial
    srand(time(0));
    int error_code, numtasks, rank, other, tag=1, msg;
    MPI_Status Stat;

    error_code = MPI_Init(&argc, &argv);
    //Parallel
    if (error_code != MPI_SUCCESS) {
        printf("Error initializing MPI enviroment.\n");
        MPI_Abort(MPI_COMM_WORLD, error_code);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (rank == 0) {
        other = 1;
        int answear = rand() % 100 + 1;
        int guess = -1;
        printf("R%d: guessed number %d \n", rank, answear);

        while(guess != answear) {
            MPI_Recv(&msg, 1, MPI_INT, other, tag, MPI_COMM_WORLD, &Stat);
            printf("R%d: received %d from %d \n", rank, msg, other);
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
        }
        msg = 0;
        printf("R%d: number correct...\n", rank);
        MPI_Send(&msg, 1, MPI_INT, other, tag, MPI_COMM_WORLD);


    } else if (rank == 1) {
        other = 0;
        msg = -1;
        int ties = 0;
        int up = 101;
        int down = 0;
        int guess = 0;

        while(msg != 0) {
            guess = (up + down) / 2;
            printf("R%d: sending %d as guess\n", rank, guess);
            MPI_Send(&guess, 1, MPI_INT, other, tag, MPI_COMM_WORLD);
            ties++;

            MPI_Recv(&msg, 1, MPI_INT, other, tag, MPI_COMM_WORLD, &Stat);
            if (msg == 1) {
                down = guess;
            } else if (msg == -1) {
                up = guess;
            }
        }
        printf("R%d: number is %d in %d tries\n", rank, guess, ties);
    } 

    MPI_Finalize();
    //Serial
    return 0;
}

//module list
//module avail
//module add mpi/openmpi-x86_64
//mpicc -O3 -lm -Wall -o mpi mpi.c
//mpirun -n 2 mpi
//mpirun --map-by core -n 2 
//for((i=0;i<20;i++)); do mpirun -n 2 mpi | grep 'number is' | cut -d' ' -f6 ; done | tee guesses.out
//awk '{sum+=$1;n++}END{print sum/n}' guesses.out



//1. implement with MPI_Sendrecv
//2. rock paper scissors with MPI_Sendrecv
//upload screenshot to SZElearning