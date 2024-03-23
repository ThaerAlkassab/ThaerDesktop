#include <stdio.h>
#include <stdlib.h>

void print_board( int * board, int N )
{
    int i, j;
    printf("\n ");
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

int nqueen( int * board, int N, int row )
{
    int ret = 0;
    int i;
    if( row >= N )
    {
//        print_board( board, N );
        return 1;
    }
    for( i = 0; i < N ; i++ )
        if( can_place( board, N, row, i ) )
        {
            board[row] = i;
            ret += nqueen( board, N, row+1 );
        }
    return ret;
}

int main( int argc, char ** argv )
{
    int N = atoi( argv[1] );
    int * board = (int *)calloc( N, sizeof(int) );
    int ret = nqueen( board, N, 0 );
    printf("%d configurations found.\n", ret);
    free(board);
    return 0;
}
