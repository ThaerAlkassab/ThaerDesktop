#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_SIZE 1000000

int max(int a, int b) { return (a > b)? a : b; }
// Returns the maximum value that can be put in a knapsack of capacity W
int knapsack(int W, int wt[], int val[], int n)
{
   int i, w;
   int K[n+1][W+1];

   // Build table K[][] in bottom up manner
//   #pragma omp parallel for schedule(static) private(i)
   for (i = 0; i <= n; i++)
   {
       #pragma omp parallel for schedule(static) private(w)
       for (w = 0; w <= W; w++)
       {
//           printf("\n i %d: w %d", i, w);
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }

   return K[n][W];
}

double gettime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + 0.000001 * tv.tv_usec;
}



int main(int argc, char * argv[])
{
//    srand(1);
//    int omp_threads_num = 4;
    double start_time = gettime();
    int i;
    int N = (int)atoll(argv[1]);
    int val[N],wt[N];
//    #pragma omp parallel for schedule(static) private(i)
    for(i=0;i<N;i++)
    {
        val[i]=rand()%150+50;
        wt[i]=rand()%5+1;
    }
    int  W = 10;
    int n = sizeof(val)/sizeof(val[0]);
    double end_time = gettime();
    printf("\nValue = %d", knapsack(W, wt, val, n));
    double elapsed_time = end_time - start_time;
    printf("\nElapsed time: %.6f seconds\n", elapsed_time);
    return 0;
}
