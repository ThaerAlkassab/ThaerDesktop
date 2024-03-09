#include <stdio.h>
#include <stdlib.h>

int answear;
int guess = -1;
int stat = 0;

void play_computer() {
    answear = rand() % 100 + 1;
    guess = -1;
    stat = 0;
    while (guess != answear) {
        stat += 1;
        printf("Guess %d.:", stat);
        scanf("%d", &guess);
        printf("\n");
        if (guess < answear) {
            printf("Need higher...\n");
        } else if (guess > answear) {
            printf("Need lower...\n");
        }
    }
    printf("Correct! You guessed in %d turn.\n", stat);
}

void play_human() {
    //setup number
    int is_end = 0;
    printf("What will be a number?: ");
    scanf("%d", &answear);
    printf("\n");
    scanf("%*[^\n]");scanf("%*c");//clear upto newline
    guess = -1;
    stat = 0;
    
    int dir = 0;
    int up = 101;
    int down = 0;
    while (is_end == 0) {
        stat += 1;
        
        //computer think
        if (up <= down) {
            printf("something wrong with these... I try again.");
            up = 101;
            down = 0;
        }
        guess = (up + down) / 2;
        
        
        //player answear for a guess
        int direction = 0;
        if (guess > answear) {
            printf("The number is %d? ([lower]/higher/correct)", guess);
            char * choose[255];
            fgets(choose, sizeof choose, stdin);
            strtok(choose, "\r\n");
            if (strcmp(choose, "higher") == 0) {
                direction = 1;
            } else if (strcmp(choose, "correct") == 0) {
                direction = 0;
            } else {
                direction = -1;
            }
        } else if (guess < answear) {
            printf("The number is %d? (lower/[higher]/correct)", guess);
            char * choose[255];
            fgets(choose, sizeof choose, stdin);
            strtok(choose, "\r\n");
            if (strcmp(choose, "lower") == 0) {
                direction = -1;
            } else if (strcmp(choose, "correct") == 0) {
                direction = 0;
            } else {
                direction = 1;
            }
        } else {
            printf("The number is %d? (lower/higher/[correct])", guess);
            char * choose[255];
            fgets(choose, sizeof choose, stdin);
            strtok(choose, "\r\n");
            if (strcmp(choose, "lower") == 0) {
                direction = -1;
            } else if (strcmp(choose, "higher") == 0) {
                direction = 1;
            } else {
                direction = 0;
            }
        }
        
        
        //computer rethink
        if (direction == 1) {
            down = guess;
        } else if (direction == -1) {
            up = guess;
        } else {
            printf("Yes! I can guess in %d turn.\n", stat);
            is_end = 1;
        }
        
    }
}

int main() {
    //setup
    srand(time(0));
    
    //choose mode
    printf("Who will guess ([player]/computer): ");
    char * choose[255];
    fgets(choose, sizeof choose, stdin);
    strtok(choose, "\r\n");
    printf("\n");
    if (strcmp(choose, "computer") == 0 || strcmp(choose, "c") == 0) {
        play_computer();
    } else {
        play_human();
    }
    printf("Thanks for playing.");
    return 0;
}