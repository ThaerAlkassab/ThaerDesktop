#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>

double get_time(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec + 0.000001 * tv.tv_usec;
}

int main(int argc, char ** argv){
    // char = one char = "c"
    // char* or char[] = string = "asdsad"
    // char** or char*[] = array of string = [char*,char*,char*,...]
    typedef float myf;
    typedef int myi;
    #define mycos(x) cosf(x)
 
    myf a = 0;
    myf b = 1.570796326794896619231321691639751442L;
    myi n = (myi) atoll(argv[1]);
    myf res = 0;
    myf dx = (b-a)/n;
    myf dxhalf = dx*0.5;
    
    double start = get_time();
    #pragma omp parallel
    {
    	myf myres = 0;
    	myi i;
        int tid = omp_get_thread_num();
        int ntr = omp_get_num_threads();
        myi my_begin = tid*n / ntr;
        myi my_end = my_begin + n / ntr;
    
        for(i=my_begin;i<my_end;i++){
            myres += ( mycos(i*dx + dxhalf));
        }
        #pragma omp atomic
        res += myres;
    }
    res *= dx;
    double end = get_time();
    
    printf("Results: %18.16Lf\n",(long double) res); 
    printf("Error: %18.16Lf\n",(long double) res - 1.0);
    printf("Time: %8.6f\n", end - start);
    return 0;
    
}
