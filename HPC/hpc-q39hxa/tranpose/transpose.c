#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef unsigned long long tint ;
typedef float tflt ;

double gettime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL); // both are output arguments. we do not need time zone -> i  t is NULL
    return tv.tv_sec + 0.000001 * tv.tv_usec;
}



// only for small matrices
void print_matrix( tint N, tflt * data )
{
    tint i, j;
    for( i = 0; i < N; i++ )
    {
        for( j = 0; j < N; j++ )
            printf("%.3f  ", data[i*N+j] );
        printf("\n");
    }
}

// for big matrices
void print_diagonalsums( tint N, tflt * data )
{
    tflt mdsum = 0;
    tflt rdsum = 0;

    tint i;
    for( i = 0; i < N ; i++ )
    {
        mdsum += data[ i*N + i ] ;
        rdsum += data[ i*N + N -1 -i ] ;
    }
    printf("Main diagonal: %le\n", (double)mdsum);
    printf("Reverse diagonal: %le\n", (double)rdsum);
}

void print_sum_by( tint N, tflt * data )
{
    tflt * rowsum = (tflt*)calloc(N,sizeof(tflt));
    tflt * colsum = (tflt*)calloc(N,sizeof(tflt));
    tint i, j;
    for( i=0; i<N; i++ )
    {
        for( j=0; j<N; j++ )
        {
            rowsum[i] += data[ i*N + j];
            colsum[j] += data[ i*N + j];
        }
    }

    printf("colsum : ");
    for(i=0;i<N;i++)
        printf(" %.3le ", colsum[i]);
    printf("\n");
    printf("rowsum : ");
    for(i=0;i<N;i++)
        printf(" %.3le ", rowsum[i]);
    printf("\n");
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
    tint N = atoi( argv[1] );
    srand(0);
    // generate a random matrix of size N by N
    tflt * data = (tflt *) malloc( N*N*sizeof(tflt) );

    tint i;
    for( i=0; i<N*N; i++ )
        // fill up with random floats from 0 to 1
        data[i] = (tflt)rand() / (tflt)RAND_MAX ;

    if( N < 11 )
    {
        print_matrix(N, data);
        print_sum_by(N, data);
    }
    print_diagonalsums(N, data);
    // transpose matrix
    double start = gettime();
    matrix_transpose(N, data);
    double end = gettime();

    if( N < 11 )
    {
        print_matrix(N, data);
        print_sum_by(N, data);
    }
    print_diagonalsums(N, data);
    free(data);
    printf("Elapsed time: %8.6f\n", end - start);
    return 0;
}