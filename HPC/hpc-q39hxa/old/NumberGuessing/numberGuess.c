#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int gen = (rand() % 100) + 1;
    int inp = 0;
    int c = 0;

    while(inp != gen){
        printf("Make your guess: ");
        scanf("%d",&inp);
        c++;
        if(inp > gen){
            printf("Smaller\n");
        }
        else if (inp < gen){
        printf("Bigger\n");
        }
    }
    printf("You guessed! You needed %d guesses.\n",c);
    return 0;
}
