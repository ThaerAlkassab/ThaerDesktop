#include <stdio.h>
#include <stdlib.h>

void print_board( int * board, int N )
{
    int i, j;
    printf("\n  ");
    for(i = 0; i <N; i++)
        printf("%c", 'A'+i);
    printf("\n");
    for(i = 0; i <N; i++)
    {
        printf("%2d", i+1);
        for(j=0;j<N;j++)
            if(board[i] == j)
                printf("*");
            else
                printf(".");
        printf("\n");
    }
}

/*
int can_put( int * board, int N, int row, int col )
{
    printf("Can put %d %d?\n", row, col);
    print_board( board, N );
    while( row >= 0 )
    {
        if( board[row-1] == col-1 )
            return 0;
        if( board[row-1] == col+1 )
            return 0;
        if( board[row-1] == col )
            return 0;
        row --;
        if( row <= 0 )
            return 1;
        if( !can_put( board, N, row, col-1 ) )
            return 0;
        if( !can_put( board, N, row, col+1 ) )
            return 0;
    }
    printf("Can put %d %d!\n", row, col);
    print_board( board, N );
    return 1;
}
*/

int can_put( int * board, int N, int row, int col )
{
    int i;
    for( i = 0; i < row; i++ )
    {
        int s = board[i];
        if( s == col )
            return 0;
        if( row - i == abs(s - col) )
            return 0;
    }
    return 1;
}


int count_queens( int * board, int N, int row )
// count possible positions on the board if
// we start to put a queen on row# row
{
    if( row == N )
    {
//        print_board( board, N );
        return 1;
    }
    int i;
    int ret = 0;
    for( i = 0; i < N; i++ )
    {
        if( can_put( board, N, row, i ) )
        {
            board[row] = i;
            ret += count_queens( board, N, row+1 );
            board[row] = -1;
        }
    }
    return ret;
}

int main(int argc, char ** argv)
{
    int N = atoi(argv[1]); // board size
    int * board = (int *)calloc( N, sizeof(int));
    int i;
    for( i = 0; i < N; i++ )
        board[i] = -1;
    int result = count_queens( board, N, 0 );
    printf("Number of possible positions: %d\n", result);
    free(board);
    return 0;
}
