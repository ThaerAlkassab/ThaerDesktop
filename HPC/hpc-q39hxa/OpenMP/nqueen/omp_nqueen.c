#include <stdio.h>
#include <stdlib.h>

int nOfMyResults = 0;
#pragma omp threadprivate(nOfMyResults)
int nOfResults = 0;

void print_board( int * board, int N )
{
    int i, j;
    printf("\n");
    printf("Thread %d\n ", omp_get_thread_num() );
    for( i = 0 ; i < N ; i++ )
        printf("%c", 'A'+i);
    printf("\n");
    for( i = 0 ; i < N ; i++ )
    {
        printf("%c", 'A'+i);
        for( j = 0; j < N ; j++ )
        if( board[i] == j )
            printf("*");
        else
            printf(".");
        printf("\n");
    }
}

int can_place( int * board, int N, int row, int place )
{
    int i;
    for( i = 0; i < row; i++ )
    {
        int q = board[i];
        if( q == place )
            return 0;
        if( q > place && (q-place == row-i) )
            return 0;
        if( q < place && (place-q == row-i) )
            return 0;
    }
    return 1;
}

int nqueen( int * board, int N, int row, int f )
{
    int ret = 0;
    int i;
    if( row >= N )
    {
//        #pragma omp critical
//        print_board( board, N );
//        return 1;
        nOfMyResults ++; 
        return;
    }
    for( i = 0; i < N ; i++ )
        if( can_place( board, N, row, i ) )
        {
//            if( row != N/2 )
            if( row != 4 )
            {
                board[row] = i;
                nqueen( board, N, row+1, 0 );
            }
            else
            {
                int * nboard = (int *)calloc( N, sizeof(int) );
                int j;
                for( j = 0; j < row; j ++ )
                    nboard[j] = board[j];
                nboard[row] = i;
                #pragma omp task
                nqueen( nboard, N, row+1, 1 );
            }
        }
    if( f )
        free( board );
//    return ret;
}

int main( int argc, char ** argv )
{
    int N = atoi( argv[1] );
    int * board = (int *)calloc( N, sizeof(int) );
    #pragma omp parallel
    {
        #pragma omp single
        nqueen( board, N, 0, 0 );
        #pragma omp barrier
        #pragma omp critical
        nOfResults += nOfMyResults;
    }
    printf("%d configurations found.\n", nOfResults);
    free(board);
    return 0;
}
