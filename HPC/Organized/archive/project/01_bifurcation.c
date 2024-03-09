#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#ifdef IS_PARALLEL
	#include <omp.h>
#endif

double gettime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + 0.000001 * tv.tv_usec;
}

int main(int argc, char * argv[]) {
	double rStart = -2.5;
	double rEnd = 4.0;
    double rDelta = 0.05;
	
	int iteration = 256;
	int settle = 64;

    // Reading in data from command line
    if (argc > 1) {
        rStart = (double) atof(argv[1]);
    }
    if (argc > 2) {
        rEnd = (double) atof(argv[2]);
    }
	if (argc > 3) {
        rDelta = (double) atof(argv[3]);
    }
	if (argc > 4) {
		settle = (double) atoll(argv[4]);
    }
	if (argc > 5) {
        iteration = (double) atoll(argv[5]);
    }
	//printf("%f %f %f\n", rStart, rEnd, rDelta);

	// Timer start
    double start = gettime();

	// Create empty file
    FILE * fptr;
    fptr = fopen("01_bifurcation.csv", "w");

	#ifdef IS_SERIAL
		double r;
		float x;
		int i;
		int j;
		int k;
		
		/* Go over range */
		for (r = rStart; r < rEnd; r+=rDelta) {
			x = 0.5;
			
			/* Reaching steady-state */
			for (i = 0; i < settle; i++) {
				x = r * x * (1 - x);
			}
			
			/* Checking oscillations and print unique */
			float * values = malloc(sizeof(float) * iteration);
			int isDone = 0;
			i = 0;
			j = 0;
			while (i < iteration && isDone == 0) {
				x = r * x * (1 - x);
				
				k = 0;
				while (k < j && x != values[k]) {
					k++;
				}
				if (k < j) {
					isDone = 1;
				} else if ((-10000 < x) && (x < 10000)) {
					values[j] = x;
					j++;
					//printf(".9g .9g\n", r, x);
					fprintf(fptr, "%.9g %.9g\n", r, x);
				}
				i++;
			}
			free(values);
		}
	#endif
	
	#ifdef IS_PARALLEL
		double r;
		float x;
		int i;
		int j;
		int k;
		
		int rIter;
		int rIterEnd = (rEnd - rStart) / rDelta;
		/* Go over range */
		#pragma omp parallel for schedule(static) private(r, x, i, j, k)
		for (rIter = 0; rIter < rIterEnd; rIter++) {
			r = rStart + rDelta * rIter;
			x = 0.5;
			
			/* Reaching steady-state */
			for (i = 0; i < settle; i++) {
				x = r * x * (1 - x);
			}
			
			/* Checking oscillations and print unique */
			float * values = malloc(sizeof(float) * iteration);
			int isDone = 0;
			i = 0;
			j = 0;
			while (i < iteration && isDone == 0) {
				x = r * x * (1 - x);
				
				k = 0;
				while (k < j && x != values[k]) {
					k++;
				}
				if (k < j) {
					isDone = 1;
				} else if ((-10000 < x) && (x < 10000)) {
					values[j] = x;
					j++;
					//printf(".9g .9g\n", r, x);
					fprintf(fptr, "%.9g %.9g\n", r, x);
				}
				i++;
			}
			free(values);
		}
	#endif
	
	// Close file
    fclose(fptr);

	// Timer end
    double end = gettime();
    printf("%f", end - start);

    return 0;
}