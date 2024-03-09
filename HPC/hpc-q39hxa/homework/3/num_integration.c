#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>
#include <mpi.h>

double gettime()
{
    return 0;//omp_get_wtime();
}

int main( int argc, char ** argv )
{
    typedef double myf;
    #define mycos(x) cos(x)
    // cosf: float, cos: double, cosl: long double
    typedef int myi;
    myf a = 0; // float, double, long double // not change
    myf b = 1.570796326794896619231321691639751442L; // not change
    myf res = 0; //change

    // loop over subintervals
    //double start = gettime();
    int numtasks, rank, dest, source = 1;
    MPI_Status Stat;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int N = numtasks;
    myf dx = (b-a)/N; // not change
    myf dxhalf = dx*0.5; // no change

    myf myres = 0;
    myi i = rank;

    myres += mycos( i*dx + dxhalf );
    MPI_Allreduce(&myres,&res,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);

    if(rank==0){    
    res *= dx;
//    double end = gettime();

//    # print results
    printf("Results: %18.16Lf\n", (long double)res);
//    # compare with analytic result (1)
    printf("Error: %18.16Lf\n", (long double)(res - 1.0));
//    printf("Time: %8.6f\n", end - start);
    }
    MPI_Finalize();
    return 0;
}