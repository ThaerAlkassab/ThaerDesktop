#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int ping = 0, pong;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        printf("This program requires exactly two processes\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        for (int i = 0; i < 10; ++i) {
            MPI_Sendrecv(&ping, 1, MPI_INT, 1, 0, &pong, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process 0 sent ping %d and received pong %d\n", ping, pong);
            ping = pong + 1;
        }
    } else if (rank == 1) {
        for (int i = 0; i < 10; ++i) {
            MPI_Sendrecv(&ping, 1, MPI_INT, 0, 0, &pong, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process 1 sent ping %d and received pong %d\n", ping, pong);
            ping = pong + 1;
        }
    }

    MPI_Finalize();
    return 0;
}
