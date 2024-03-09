#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>
#include <mpi.h>


int main( int argc, char ** argv )
{
    typedef double myf;
    #define mycos(x) cos(x)
   
    typedef int myi;
    myf a = 0; 
    myf b = 1.570796326794896619231321691639751442L;
    myf res = 0; 

    int numtasks, rank, dest, source = 1;
    MPI_Status Stat;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int N = numtasks;
    myf dx = (b-a)/N; 
    myf dxhalf = dx*0.5; 

    myf myres = 0;
    myi i = rank;

    myres += mycos( i*dx + dxhalf );
    MPI_Allreduce(&myres,&res,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);

    if(rank==0){    
    res *= dx;

    printf("Results: %18.16Lf\n", (long double)res);

    printf("Error: %18.16Lf\n", (long double)(res - 1.0));

    }
    MPI_Finalize();
    return 0;
}