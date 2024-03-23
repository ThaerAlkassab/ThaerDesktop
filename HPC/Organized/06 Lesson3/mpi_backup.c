#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

typedef unsigned long long MyInt;
typedef float MyFloat;
#define MY_MPI_FLOAT MPI_FLOAT

int myrank, ranks;
MyInt N, rlow, rhigh, nrows, rem;
MyFloat *data;

double gettime() {
    return MPI_Wtime();
}

void print_matrix() {
    MPI_Status Stat;
    char c = "x";
    
    if (myrank > 0) {
        MPI_Recv(&c, 1, MPI_CHAR, myrank - 1, 1, MPI_COMM_WORLD, &Stat);
    }
    MyInt i, j;
    for (i = 0; i < nrows; i++) {
        printf("%d:%d ", myrank, i + rlow);
        for (j = 0; j < N; j++) {
            printf("%.3f  ", data[i * N + j]);
        }
        printf("\n");
    }
    if (myrank < ranks - 1) {
        MPI_Send(&c, 1, MPI_CHAR, myrank + 1, 1, MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

void print_diagonalsums() {
    MyFloat mdsum = 0;
    MyFloat rdsum = 0;

    MyInt i;
    for (i = rlow; i < rhigh; i++) {
        mdsum += data[(i - rlow) * N + i];
        rdsum += data[(i - rlow) * N + N - 1 - i];
    }
    if (myrank == 0) {
        MPI_Reduce(MPI_IN_PLACE, &mdsum, 1, MY_MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(MPI_IN_PLACE, &rdsum, 1, MY_MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
        printf("Main diagonal: %le\n", (double) mdsum);
        printf("Reverse diagonal: %le\n", (double) rdsum);
    } else {
        MPI_Reduce(&mdsum, NULL, 1, MY_MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(&rdsum, NULL, 1, MY_MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

void print_sum_by() {
    MyFloat *rowsum = (MyFloat*)calloc(N, sizeof(MyFloat));
    MyFloat *colsum = (MyFloat*)calloc(N, sizeof(MyFloat));
    MyInt i, j;
    for (i = rlow; i < rhigh; i++) {
        for (j = 0; j < N; j++) {
            rowsum[i] += data[(i - rlow) * N + j];
            colsum[j] += data[(i - rlow) * N + j];
        }
    }

    if (myrank == 0) {
        MPI_Reduce(MPI_IN_PLACE, colsum, N, MY_MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(MPI_IN_PLACE, rowsum, N, MY_MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
        printf("colsum : ");
        for (i = 0; i < N; i++) {
            printf(" %.3le ", colsum[i]);
        }
        printf("\n");
        printf("rowsum : ");
        for (i = 0; i < N; i++) {
            printf(" %.3le ", rowsum[i]);
        }
        printf("\n");
    } else {
        MPI_Reduce(colsum, NULL, N, MY_MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(rowsum, NULL, N, MY_MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    }
    free(colsum);
    free(rowsum);
    MPI_Barrier(MPI_COMM_WORLD);
}

void matrix_transpose() {
    MyFloat *d2 = (MyFloat*)calloc(nrows * N, sizeof(MyFloat));
    // N rows and nrows columns
    MPI_Request *SReqs = (MPI_Request*)malloc(nrows * ranks * sizeof(MPI_Request));
    MPI_Request *RReqs = (MPI_Request*)malloc(nrows * ranks * sizeof(MPI_Request));

    // gather data to d2
    MyInt c, i, j;
    for (c = 0; c < ranks; c++) {
        if (c == myrank) {
            for (i = 0; i < nrows; i++) {
                for (j = 0; j < nrows; j++) {
                    MyInt row_index = (i * N) + rlow + j;
                    MyInt col_index = (rlow + i) * nrows + j;
                    d2[col_index] = data[row_index];
                }
            }
                    
        } else {
            for (i = 0; i < nrows; i++) {
                MPI_Isend(data + i * N + c * nrows, nrows, MY_MPI_FLOAT, c, i, MPI_COMM_WORLD, SReqs + c * nrows + i);
            }
            
            for (i = 0; i < nrows; i++) {
                MPI_Irecv(d2 + c * nrows * nrows + i * nrows, nrows, MY_MPI_FLOAT, c, i, MPI_COMM_WORLD, RReqs + c * nrows + i);
            }
               
        }
    }
    // make sure that all Isends/Irecvs are completed
    MPI_Status *Stats = (MPI_Status*)malloc(nrows * sizeof(MPI_Status));
    for (c = 0; c < ranks; c++) {
        if (c != myrank) {
            // make sure that all sends with rank c are done
            MPI_Waitall(nrows, SReqs + c * nrows, Stats);
            // make sure that all recvs with rank c are done
            MPI_Waitall(nrows, RReqs + c * nrows, Stats);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    free(Stats);

    // transpose data in d2 to data
    for (i = 0; i < N; i++) {
        for (j = 0; j < nrows; j++) {
            data[j * N + i] = d2[i * nrows + j];
        }
    }
    
    free(d2);
    free(SReqs);
    free(RReqs);
    MPI_Barrier(MPI_COMM_WORLD);
}

int main(int argc, char ** argv) {
    //read Matrix size
    N = atoi(argv[1]);

    //Init MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &ranks);
    srand(3 + myrank);
    
    //setup borders, length and data
    rlow = (N / ranks) * myrank;
    rhigh = (N / ranks) * (myrank + 1);
    rem = N % ranks;
    if (myrank < rem) {
        rlow += myrank;
        rhigh += myrank + 1;
    } else {
        rlow += rem;
        rhigh += rem;
    }
    nrows = rhigh - rlow;

    // generate a random matrix of size N by N
    data = (MyFloat*)malloc(nrows * N * sizeof(MyFloat));
    MyInt i;
    for (i = 0; i < nrows * N; i++) {
        data[i] = (MyFloat)rand()/(MyFloat)RAND_MAX;
    }

    //print borders
    printf("I am rank %d and I am managing rows %d to %d\n", myrank, rlow, rhigh - 1);
    MPI_Barrier(MPI_COMM_WORLD);
    if (myrank == 0) {
        printf("%d \n", nrows * N);
    }

    //print check sum and matrix
    if (N < 11) {
        print_matrix();
        print_sum_by();
    }
    print_diagonalsums();

    // transpose matrix
    double start = gettime();
    matrix_transpose();
    double end = gettime();

    //print matrix
    if (N < 11) {
        print_matrix();
        print_sum_by();
    }
    print_diagonalsums();

    free(data);
    printf("Elapsed time: %8.6f\n", end - start);
    MPI_Finalize();
    return 0;
}

//module list
//module avail
//module add mpi/openmpi-x86_64
//mpicc -O3 -lm -Wall -o mpi mpi.c
//mpirun -n 2 mpi 4
//mpirun --map-by core -n 4 ./mpi

//   rm -f /dev/shm/*