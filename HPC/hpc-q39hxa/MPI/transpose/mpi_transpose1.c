#include <stdio.h>
#include <stdlib.h>
// #include <sys/time.h>
#include <mpi.h>
#include <string.h>

typedef int tint ;
#define MY_MPI_INT_TYPE MPI_INT
typedef float tflt ;
#define MY_MPI_FLOAT_TYPE MPI_FLOAT

int myrank, ranks;
tint N, rlow, rhigh, nrows, rem ;
tint * rlows;
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

void matrix_transpose()
{
    // data is not transposed
    tflt * d2 = (tflt *)malloc( nrows * N * sizeof(tflt) );
    tint i, j, c;
    tflt s;
    MPI_Request * SReqs = (MPI_Request *)malloc( nrows * ranks * sizeof(MPI_Request) );
    MPI_Request * RReqs = (MPI_Request *)malloc( N * sizeof(MPI_Request) );
    MPI_Status * SStats = (MPI_Status *)malloc( nrows );
    MPI_Status * RStats = (MPI_Status *)malloc( nrows+1 );
    

    for( c = 0; c < ranks; c++ )
    {
        if( c == myrank )
        {
            // copy my data to d2
            printf("R%d memcpy\n", myrank);
            for( i = rlow; i < rhigh; i++ )
                for( j = rlow; j < rhigh; j++ )
                    d2[ i * nrows + j ] = data[ (i-nrows) * N + j] ;
//                memccpy( d2+i*nrows, data+(i-nrows)*N, rhigh-rlow, sizeof(tflt) );
            printf("R%d memcpy done\n", myrank);
        }
        else
        {
            printf("R%d comm to %d\n", myrank, c);
            for( i = rlow; i < rhigh; i++ )
                MPI_Isend( data + (i-rlow)*N + rlows[c], rlows[c+1]-rlows[c], MY_MPI_FLOAT_TYPE,
                           c, i, MPI_COMM_WORLD, SReqs+c*nrows+(i-rlow) );
            for( i = rlows[c]; i < rlows[c+1]; i++ )
                MPI_Irecv( d2 + i * nrows, nrows, MY_MPI_FLOAT_TYPE,
                           c, i, MPI_COMM_WORLD, RReqs+i );
            printf("R%d comm to %d done\n", myrank, c);
        }
    } 

    for( c = 0 ; c < ranks; c++ )
    {
        if( c != myrank )
        {
            printf("R%d wait on comm to %d\n", myrank, c);
            MPI_Waitall( nrows, SReqs + c*nrows, SStats );
            MPI_Waitall( rlows[c+1] - rlows[c], RReqs+rlows[c], RStats );
            printf("R%d wait on comm to %d done\n", myrank, c);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);

    // just transpose all to data
    printf("R%d transpose\n", myrank);
    for( i = 0; i < N ; i++ )
        for( j = 0; j < nrows; j++ )
            data[ j*N+i ] = d2[ i*nrows + j ];
    printf("R%d transpose done\n", myrank);
    MPI_Barrier(MPI_COMM_WORLD);
        
    free(d2);
    printf("R%d free d2 done\n", myrank);
    free(SReqs);
    printf("R%d free sreq done\n", myrank);
    free(RReqs);
    printf("R%d free rreq done\n", myrank);
    free(SStats);
    printf("R%d free sstats done\n", myrank);
}

int main(int argc, char ** argv)
{
    tint i;

    MPI_Init( & argc, &argv );

    
//    int myrank, ranks;
    MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
    MPI_Comm_size( MPI_COMM_WORLD, &ranks );
    rlows = (tint *) calloc( (ranks + 1), sizeof(tint) );
    
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
    
    MPI_Allgather( &rlow, 1, MY_MPI_INT_TYPE, rlows, 1, MY_MPI_INT_TYPE, MPI_COMM_WORLD );
    rlows[ranks] = N;

    printf("I am rank %d and I am managing rows %d to %d\n", myrank, rlow, rhigh-1 );
    printf("R%d rlows: ", myrank);
    for( i = 0; i<=ranks; i++ )
        printf("%d ", rlows[i]);
    printf("\n");

    srand(3+myrank);
    nrows = rhigh - rlow;
    // generate a random matrix of size N by N
    data = (tflt *) malloc( nrows*N*sizeof(tflt) );
    
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
    // return 0;
    // transpose matrix
    double start = gettime();
    matrix_transpose();
    double end = gettime();
    
    printf("R%d Elapsed time: %8.6f\n", myrank, end - start);
    if( N < 11 )
    {
        print_matrix();
        print_sum_by();
    }
    print_diagonalsums();
    free(data);
    printf("R%d Elapsed time: %8.6f\n", myrank, end - start);
    return 0;
}
