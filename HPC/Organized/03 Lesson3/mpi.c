#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <mpi.h>

double gettime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + 0.000001 * tv.tv_usec;
}

int main(int argc, char ** argv) {
    srand(time(0));

    int rank;
    int ranks;
    int error_code = MPI_Init(&argc, &argv);
    if (error_code != MPI_SUCCESS) {
        printf("Error initializing MPI enviroment.\n");
        MPI_Abort(MPI_COMM_WORLD, error_code);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &ranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    double a = 0.0;
    double b = M_PI / 2.0;
    int N = atoll(argv[1]);
    double res = 0.0;
    double dx = (b-a) / N;
    double dx_half = dx * 0.5;

    int s_split = N / ranks;
    int s_start = s_split * rank;
    int s_end = s_start + s_split;
    if (rank == ranks-1) {
        s_end = N;
    }

    double start = gettime();
    int i = 0;
    double myres = 0.0;
    for (i=s_start; i < s_end; i++) {
        myres += cos(i*dx + dx_half);
    }
    double end = gettime();

    MPI_Allreduce(&myres, &res, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    if (rank == 0) {
        res *= dx;
        double err = res - 1;
        printf("%d \t", N);
        printf("%16.18f \t", fabs(err));
        printf("%16.18f \n", end-start);
    }
    
    


    MPI_Finalize();
    return 0;
}

//module list
//module avail
//module add mpi/openmpi-x86_64
//mpicc -O3 -lm -Wall -o mpi mpi.c
//mpirun -n 4 mpi 100
//mpirun --map-by core -n 4 ./mpi 100
//mpirun -n 1 master : -n 1 slave1 : -n 1 slave2