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

    if (rank != 0){
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    
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
    MPI_Finalize();
    return 0;
}