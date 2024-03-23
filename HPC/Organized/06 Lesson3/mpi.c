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

MyInt calc_rlow(int rank) {
    MyInt before_nrows = (N / ranks) * rank;
    if (rank < rem) {
        before_nrows += rank;
    } else {
        before_nrows += rem;
    }
    return before_nrows;
}
MyInt calc_nrows(int rank) {
    MyInt nrows = N / ranks;
    if (rank < rem) {
        nrows += 1;
    }
    return nrows;
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
    for (i = 0; i < nrows; i++) {
        mdsum += data[(i * N) + (i + rlow)];
        rdsum += data[(i * N) + (N - 1) - (i + rlow)];
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
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < N; j++) {
            rowsum[i + rlow] += data[i * N + j];
            colsum[j] += data[i * N + j];
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
    MyFloat *d2 = (MyFloat*)calloc(N * nrows, sizeof(MyFloat));
    // Request for each row and each rank
    MPI_Request *SReqs = (MPI_Request*)malloc((nrows * ranks + rem) * sizeof(MPI_Request));
    MPI_Request *RReqs = (MPI_Request*)malloc((nrows * ranks + rem) * sizeof(MPI_Request));

    // Types
    MPI_Datatype numberType;
    MPI_Type_contiguous(1, MY_MPI_FLOAT, &numberType);
    MPI_Type_commit(&numberType);

    // gather data to d2
    MyInt i, j;
    int rank;
    for (rank = 0; rank < ranks; rank++) {
        if (rank == myrank) {
            //switch locally
            for (i = 0; i < nrows; i++) {
                for (j = 0; j < nrows; j++) {
                    MyInt row_index = (i * N) + rlow + j;
                    MyInt col_index = (rlow + i) * nrows + j;
                    d2[col_index] = data[row_index];
                }
            }
                    
        } else {
            //calculate the rank's rlow and nrows
            MyInt rank_rlow = calc_rlow(rank);
            MyInt rank_nrows = calc_nrows(rank);
            //send to others
            for (i = 0; i < nrows; i++) {
                MPI_Isend(data + i * N + rank_rlow, rank_nrows, numberType, rank, i, MPI_COMM_WORLD, SReqs + rank * nrows + i);
                //printf("D%d: a %d %d\n", myrank, rank_rlow, i);
            }
            //recievs from others
            for (i = 0; i < rank_nrows; i++) {
                MPI_Irecv(d2 + rank_rlow * nrows + i * nrows, nrows, numberType, rank, i, MPI_COMM_WORLD, RReqs + rank_rlow + i);
                //printf("D%d: b %d %d\n", myrank, rank_rlow, i);
            }
            
        }
    }
    // make sure that all Isends/Irecvs are completed
    MPI_Status *Stats = (MPI_Status*)malloc(N * sizeof(MPI_Status));
    for (rank = 0; rank < ranks; rank++) {
        
        if (rank != myrank) {
            MyInt rank_rlow = calc_rlow(rank);
            MyInt rank_nrows = calc_nrows(rank);

            //printf("D%d: c %d %d\n", myrank, rank,  nrows);
            // make sure that all sends with rank c are done
            MPI_Waitall(nrows, SReqs + rank * nrows, Stats);

            //printf("D%d: d %d %d\n", myrank, rank,  nrows);
            // make sure that all recvs with rank c are done
            MPI_Waitall(rank_nrows, RReqs + rank_rlow, Stats);
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
    rem = N % ranks;
    rlow = calc_rlow(myrank);
    nrows = calc_nrows(myrank);
    rhigh = rlow + nrows;

    // generate a random matrix of size N by N
    data = (MyFloat*)malloc(nrows * N * sizeof(MyFloat));
    MyInt i;
    for (i = 0; i < N * nrows; i++) {
        data[i] = (MyFloat)rand()/(MyFloat)RAND_MAX;
    }

    //print borders
    printf("R%d: Managing %d to %d = %d nrow\n", myrank, rlow, rhigh - 1, nrows);
    /*if (myrank == 0) {
        printf("%d \n", nrows * N);
    }*/
    MPI_Barrier(MPI_COMM_WORLD);

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
    if (myrank == 0) {
        printf("Elapsed time: %8.6f\n", end - start);
    }
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