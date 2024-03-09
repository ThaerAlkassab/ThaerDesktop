#include <stdio.h>
#include <math.h>
#include <omp.h>

#define res_cal 0.68268948119303L //interval a=-2, b=2, mean = 0, std = 1
typedef long double myf;
typedef int myi;

double get_time(){
    return omp_get_wtime();
}


myf gauss_bell_formula(myf x, myf mean, myf std){
    return  1/(std*sqrt(2*M_PI)) *exp(pow((x-mean)/(std),2) * -0.5); 
}

int main(int argc, char ** argv)
{
    //Initial parameters user input
    myf a = -1; // start point
    myf b = 1; // end point 
    myf mean = 0; //mean of the bell
    myf std = 1; //std of the bell
    myi n = (myi) atoll(argv[1]); // number of intervals (myi)atoll(argv[1])
    
    myf h = (b-a)/n; //interval width
    myf res; // result of integral
    myf x1;
    myf x2;
    myi i;

    double start = get_time();
    
    #pragma omp parallel for private(x1,x2,i) reduction(+:res)
    for (i = 1; i < n; i++) { /* (n-1) iterations */
        x1 = a  + i* h;
        if (i%2 == 0){
            res += 2.0*gauss_bell_formula(x1,mean,std);
        }
        else{
            res += 4.0*gauss_bell_formula(x1,mean,std);
        }
    }
    
    res += (gauss_bell_formula(a,mean,std) + gauss_bell_formula(b,mean,std));
    res *= h/3.0;

    double end = get_time();
    
    //print results
    printf("Results: %18.16Lf\n", (long double)res);
    printf("Error: %18.16Lf\n", (long double)(res-res_cal));
    printf("Time: %8.6f\n", end - start);
    return 0;

}