#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand( time( NULL ) );
    int gen = rand() % 100 + 1;
    int inp = -1;
    int c = 0;

    while( inp != gen )
    {
        printf("Tell me your guess: ");
        scanf("%d", &inp);
        c++;
        if( inp > gen )
            printf("Need smaller number!\n");
        else if( inp < gen )
            printf("Need bigger number!\n");
    }
    printf("You guessed the number! You needed %d guesses.\n", c);
    return 0;
}
