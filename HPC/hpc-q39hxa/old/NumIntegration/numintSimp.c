#include <stdio.h>
#include <math.h>
#include <sys/time.h>

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
    myf b = 3.14/2;
    myi n = (myi) atoll(argv[1]);
    myf res = 0;
    myi i;
    myf h = (b-a)/n;
    myi multi = 4;
    myf xi = a + h;
    
    double start = get_time();
    for(i=0;i<n-1;i++){
        res += multi * mycos(xi );
        xi += h;
        if(multi == 4){multi = 2;}
        else{multi = 4;}
        }
    res += (mycos(a) + mycos(b));
    res *= ((1.0/3)*h);
    double end = get_time();
    
    printf("Results: %18.16Lf\n",(long double) res); 
    printf("Error: %18.16Lf\n",(long double) res - 1.0);
    printf("Time: %8.6f\n", end - start);
    return 0;
    
}
