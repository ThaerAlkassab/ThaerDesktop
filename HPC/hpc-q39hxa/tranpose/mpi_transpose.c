#include <stdio.h>
#include <stdlib.h>
// #include <sys/time.h>
#include <mpi.h>

typedef unsigned long long tint ;
typedef float tflt ;
#define MY_MPI_FLOAT_TYPE MPI_FLOAT

int myrank, ranks;
tint N, rlow, rhigh, nrows, rem ;
tflt * data;

double gettime()
{
    return MPI_Wtime();
//    struct timeval tv;
//    gettimeofday(&tv, NULL); // both are output arguments. we do not need time zone -> i  t is NULL
//    return tv.tv_sec + 0.000001 * tv.tv_usec;
}

// only for small matrices
void print_matrix()
{
    tint i, j;
    char c = 'x';
    MPI_Status Stat;
    if( myrank > 0 )
        MPI_Recv( &c, 1, MPI_CHAR,
                  myrank-1, 1, MPI_COMM_WORLD, &Stat);
    for( i = 0; i < nrows; i++ )
    {
        printf("%d:%d ", myrank, i+rlow );
        for( j = 0; j < N; j++ )
            printf("%.3f  ", data[i*N+j] );
        printf("\n");
    }
    if( myrank < ranks - 1)
        MPI_Send( &c, 1, MPI_CHAR,
                  myrank+1, 1, MPI_COMM_WORLD );
}

// for big matrices
void print_diagonalsums( )
{
    tflt mdsum = 0;
    tflt rdsum = 0;


    tint i;
    for( i = rlow; i < rhigh ; i++ )
    {
        mdsum += data[ (i-rlow)*N + i ] ;
        rdsum += data[ (i-rlow)*N + N -1 -i ] ;
    }
    if(myrank == 0)
    {
        MPI_Reduce( MPI_IN_PLACE, &mdsum, 1, MY_MPI_FLOAT_TYPE,
                    MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce( MPI_IN_PLACE, &rdsum, 1, MY_MPI_FLOAT_TYPE,
                    MPI_SUM, 0, MPI_COMM_WORLD);
        printf("Main diagonal: %le\n", (double)mdsum);
        printf("Reverse diagonal: %le\n", (double)rdsum);
    }
    else
    {
        MPI_Reduce( &mdsum, NULL, 1, MY_MPI_FLOAT_TYPE,
                    MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce( &rdsum, NULL, 1, MY_MPI_FLOAT_TYPE,
                    MPI_SUM, 0, MPI_COMM_WORLD);
    }
}

void print_sum_by( )
{
    tflt * rowsum = (tflt*)calloc(N,sizeof(tflt));
    tflt * colsum = (tflt*)calloc(N,sizeof(tflt));
    tint i, j;
    for( i=rlow; i<rhigh; i++ )
    {
        for( j=0; j<N; j++ )
        {
            rowsum[i] += data[ (i-rlow)*N + j];
            colsum[j] += data[ (i-rlow)*N + j];
        }
    }

    if( myrank == 0 )
    {
        MPI_Reduce( MPI_IN_PLACE, colsum, N,
                    MY_MPI_FLOAT_TYPE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce( MPI_IN_PLACE, rowsum, N,
                    MY_MPI_FLOAT_TYPE, MPI_SUM, 0, MPI_COMM_WORLD);
        printf("colsum : ");
        for(i=0;i<N;i++)
            printf(" %.3le ", colsum[i]);
        printf("\n");
        printf("rowsum : ");
        for(i=0;i<N;i++)
            printf(" %.3le ", rowsum[i]);
        printf("\n");
    }
    else
    {
        MPI_Reduce( colsum, NULL, N,
                    MY_MPI_FLOAT_TYPE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce( rowsum, NULL, N,
                    MY_MPI_FLOAT_TYPE, MPI_SUM, 0, MPI_COMM_WORLD);
    }
    free(colsum); free(rowsum);
}

void matrix_transpose(tint N, tflt * data)
{
    tint i, j;
    tflt s;
    for( i = 0; i < N ; i++ )
        for( j = i+1; j < N; j++ )
        {
            s = data[ i*N+j ];
            data[ i*N+j ] = data[ j*N+i ];
            data[ j*N+i ] = s;
        }
}

int main(int argc, char ** argv)
{
    MPI_Init( & argc, &argv );

//    int myrank, ranks;
    MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
    MPI_Comm_size( MPI_COMM_WORLD, &ranks );

    N = atoi( argv[1] );
    rlow = (N / ranks) * myrank;
    rhigh = (N / ranks) * (myrank+1);
    rem = N % ranks;
    if( myrank < rem )
    {
        rlow += myrank;
        rhigh += myrank +1;
    }
    else
    {
        rlow += rem ;
        rhigh += rem ;
    }
    printf("I am rank %d and I am managing rows %d to %d\n", myrank, rlow, rhigh-1 );

    srand(3+myrank);
    nrows = rhigh - rlow;
    // generate a random matrix of size N by N
    data = (tflt *) malloc( nrows*N*sizeof(tflt) );

    tint i;
    for( i=0; i<nrows*N; i++ )
        // fill up with random floats from 0 to 1
        data[i] = (tflt)rand() / (tflt)RAND_MAX ;

    MPI_Barrier(MPI_COMM_WORLD);
    if( N < 11 )
    {
        print_matrix();
        print_sum_by();
    }
    print_diagonalsums();
    return 0;
    // transpose matrix
    double start = gettime();
    matrix_transpose();
    double end = gettime();

    if( N < 11 )
    {
        print_matrix();
        print_sum_by();
    }
    print_diagonalsums();
    free(data);
    printf("Elapsed time: %8.6f\n", end - start);
    return 0;
}