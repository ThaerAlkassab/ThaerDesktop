#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    int numtasks, rank, dest, sender, rc, count, tag = 1;
    char inmsg,outmsg='x';
    MPI_Status Stat;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank ==0)
    {
        dest = 1;
        rc = MPI_Sendrecv(&outmsg,1,MPI_CHAR,dest,tag
                        ,&inmsg,1,MPI_CHAR,dest,tag
                        ,MPI_COMM_WORLD,&Stat);
        printf("R%d received %c from %d\n",rank,inmsg,dest);
    }
    else if (rank == 1)
    {
        dest = 0;
        rc = MPI_Sendrecv(&outmsg,1,MPI_CHAR,dest,tag
                        ,&inmsg,1,MPI_CHAR,dest,tag
                        ,MPI_COMM_WORLD,&Stat);
        printf("R%d received %c from %d\n",rank,inmsg,dest);

    }
    MPI_Finalize();
    return 0;
}