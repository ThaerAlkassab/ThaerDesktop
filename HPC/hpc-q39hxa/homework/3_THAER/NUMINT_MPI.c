#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <mpi.h>

#define M_PI 3.14159265358979323846

double gettime() {
    //time function
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + 0.000001 * tv.tv_usec;
}

int main(int argc, char ** argv) {
    srand(time(0)); //seed

    int rank, ranks, i=0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double a = 0.0;
    double b = M_PI / 2.0;
    int N = atoll(argv[1]);
    double res = 0.0;
    double dx = (b-a) / N;
    double dx_half = dx * 0.5;

    int n = N / ranks; // Divide the workload among ranks
    int n1 = n * rank; // start the intervals to be computed by the current MPI process
    int nN = n1 + n;   // end the intervals to be computed by the current MPI process
    // To ensure that all intervals are computed
    if (rank == ranks-1) {
        nN = N;
    }

    double start = gettime(); // start the time
    double myres = 0.0;
    for (i=n1; i < nN; i++) {
        myres += cos(i*dx + dx_half);
    }
    double end = gettime(); // end the time
    // MPI
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
