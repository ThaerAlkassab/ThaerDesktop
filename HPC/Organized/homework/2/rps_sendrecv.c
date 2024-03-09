#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char ** argv) {
    //Serial
    int error_code, rank, other, tag=1;
    MPI_Status Stat;

    error_code = MPI_Init(&argc, &argv);
    //Parallel
    if (error_code != MPI_SUCCESS) {
        printf("Error initializing MPI enviroment.\n");
        MPI_Abort(MPI_COMM_WORLD, error_code);
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (rank == 0) {
        unsigned int seed_r = time(0) + rank;
        int N = 10;
        int n = 0;
        if (argc > 1) {
            N = (int) atoll(argv[1]);
        }
        other = 1;
        int win = 0;
        int loss = 0;

        int msg = 0;
        while(n < N) {
            int guess = rand_r(&seed_r) % 3; // 0-paper, 1-scissors, 2-rock, 3-end
            MPI_Sendrecv(&guess, 1, MPI_INT, other, tag, &msg, 1, MPI_INT, other, tag, MPI_COMM_WORLD, &Stat);
            printf("R%d: I show ", rank);
            if (guess == 0) {
                printf("paper");
            } else if (guess == 1) {
                printf("scissors");
            } else {
                printf("rock");
            }
            printf(" others show ");
            if (msg == 0) {
                printf("paper");
            } else if (msg == 1) {
                printf("scissors");
            } else {
                printf("rock");
            }

            if (guess == 0) {
                if (msg == 1) {
                    loss++;
                } else if (msg == 2) {
                    win++;
                }
            } else if (guess == 1) {
                if (msg == 2) {
                    loss++;
                } else if (msg == 0) {
                    win++;
                }
            } else {
                if (msg == 0) {
                    loss++;
                } else if (msg == 1) {
                    win++;
                }
            }
            n++;
            printf(" \n");
        }
        
        msg = 3;
        MPI_Send(&msg, 1, MPI_INT, other, tag, MPI_COMM_WORLD);
        printf("R%d: I won %d times, others wons %d times, %d were same...\n", rank, win, loss, N-win-loss);

    } else if (rank == 1) {
        unsigned int seed_r = time(0) + rank;
        other = 0;
        int msg = -1;

        while(msg != 3) {
            MPI_Recv(&msg, 1, MPI_INT, other, tag, MPI_COMM_WORLD, &Stat);
            if (msg == 3) {
                break;
            }
            msg = rand_r(&seed_r) % 3;
            MPI_Send(&msg, 1, MPI_INT, other, tag, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    //Serial
    return 0;
}

//module list
//module avail
//module add mpi/openmpi-x86_64
//mpicc -O3 -lm -Wall -o rps_sendrecv rps_sendrecv.c
//mpirun -n 2 rps_sendrecv
//mpirun --map-by core -n 2 
//for((i=0;i<20;i++)); do mpirun -n 2 mpi | grep 'number is' | cut -d' ' -f6 ; done | tee guesses.out
//awk '{sum+=$1;n++}END{print sum/n}' guesses.out