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

void matrix_transpose()
{
    tflt * d2 = (tflt *)calloc( nrows * N, sizeof(tflt) );
    // N rows and nrows columns
    tint i, j, c;
    tflt s;
    MPI_Request * SReqs = (MPI_Request *)malloc( nrows * ranks * sizeof(MPI_Request) );
    MPI_Request * RReqs = (MPI_Request *)malloc( nrows * ranks * sizeof(MPI_Request) );
    

    // gather data to d2
    for( c = 0; c < ranks; c++ )
    {
        if( c == myrank )
        {
            for( i = 0 ; i < nrows ; i++ )
                for( j = 0; j < nrows ; j++ )
//                    d2[ i * N + rlow + j] = data[ (i + rlow) * nrows + j ];
                    d2[ (i+rlow)*nrows + j ] = data[ i*N+rlow+j ];
        }
        else
        {
            for( i = 0; i < nrows ; i++ )
                MPI_Isend( data+i*N+c*nrows, nrows, MY_MPI_FLOAT_TYPE,
                           c, i, MPI_COMM_WORLD, SReqs +c*nrows+i);
            for( i = 0; i < nrows ; i++ )
                MPI_Irecv( d2 + c*nrows*nrows +i*nrows, nrows, MY_MPI_FLOAT_TYPE,
                           c, i, MPI_COMM_WORLD, RReqs +c*nrows+i);
        }
    } 
    // make sure that all Isends/Irecvs are completed
    MPI_Status * Stats = (MPI_Status *)malloc( nrows*sizeof(MPI_Status) );
    for( c = 0; c < ranks ; c++)
    {
        if( c != myrank )
        {
            // make sure that all sends with rank c are done
            MPI_Waitall( nrows, SReqs +c*nrows, Stats );
            // make sure that all recvs with rank c are done
            MPI_Waitall( nrows, RReqs +c*nrows, Stats );
        }
    }
    free(Stats);
    // transpose data in d2 to data
    for( i = 0; i < N ; i++ )
        for( j = 0; j < nrows; j++ )
            data[j * N + i ] = d2[i * nrows + j];

    MPI_Barrier(MPI_COMM_WORLD);
    free(d2);
    free(SReqs);
    free(RReqs);
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
//    return 0;
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
    MPI_Barrier(MPI_COMM_WORLD);
    free(data);
    printf("Elapsed time: %8.6f\n", end - start);
    MPI_Finalize();
    return 0;
}
