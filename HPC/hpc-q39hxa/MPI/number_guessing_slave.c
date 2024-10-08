#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char * argv[])
{
    int numtasks, rank, dest, source, rc, count, tag = 1;
    char inmsg,outmsg='x';
    MPI_Status Stat;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    srand( time(NULL));
    
    if (rank ==0)
    {
        int answer = rand() % 100 + 1;
        int guess;
        int num = 0;
        int hint = 1; //hint -1 means lower, 0 is correct, +1 higher
        
        dest = 1;
        source = 1;
        printf("R%d: My  number is %d, guess it. \n",rank,answer);
        
        for(; guess != answer; num++){
        
            MPI_Bcast(&guess,1,MPI_INT,num % (numtasks-1) + 1 , MPI_COMM_WORLD);
            //rc = MPI_Recv(&guess,1,MPI_INT,source,tag,MPI_COMM_WORLD,&Stat);
            if (guess < answer){hint = 1;}
            else if (guess > answer) {hint = -1;}
            else{ hint = 0;}
            MPI_Bcast(&hint,1,MPI_INT,rank , MPI_COMM_WORLD);
        }
        fprintf(stdout,"R0: Rank %d has guessed the number in %d \n",(num-1)%(numtasks-1)+1, num);       
    }
    
    else
    {
        rand();
        int lower = 1;
        int maxi = 100;
        int guess;
        int hint = -2;
        int c = 0;
        
        while(hint != 0){
        
            if (c%(numtasks-1)+1==rank){
                int a = maxi - lower;
                guess = (rand() % (a + 1)) + lower;

                printf("R%d: I am guess %d\n",rank,guess);
                MPI_Bcast(&guess,1,MPI_INT,rank,MPI_COMM_WORLD);
            }
            else{
                MPI_Bcast(&guess,1,MPI_INT,c%(numtasks-1)+1,MPI_COMM_WORLD);
            }
            MPI_Bcast(&hint,1,MPI_INT,0,MPI_COMM_WORLD);
    	    if(hint == 1){
                printf("higher\n");
                lower = guess+1;  
            }
            if(hint == -1){
                printf("lower\n");
                maxi = guess-1;
            }
            c++;
        }
    }
    MPI_Finalize();
    return 0;
}