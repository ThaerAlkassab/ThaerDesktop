#include <stdlib.h>

void printout(double t, double * T, int N) {
	int i;
	int imax = 10;
	printf("%8.0f ", t);
	for (i=0; i < imax; i++) {
		int idx = i*(N+1)/(imax-1)-1;
		double Ti = T[idx];
		printf("%7.2f ", Ti - 273.0);
	}
	printf("\n");
}

int main(int argc, char ** argv) {
	int	i;	//indexing space
	int	t;	//indexing time

	int	N = 1024;	//number of cells
	int	time = 512000;	//number of time steps
	int	printtime = time / 20;

	double	Tinit = 300.0;	//Initial temp
	double	T1 = 1000.0;	// BC hot
	double	T2 = 200.0;	// BC cold

	double	dx = 0.01;	// size of cells (m)
				// L = N*dx
				// L = 20.24 (m)
	double	dt = 0.001;	// time step (s)
				// tau = time*dt
				// tau = 1.024 (s)
	double	alpha = 0.03;	//condition coefficient

	double	k = alpha * dt / dx / dx;

	double	*T = (double *)malloc((N+2) * sizeof(double)) + 1;
	double DT = 0.0;
	double v = 0.0;

	for(i=1; i<N; i++) {
		T[i] = Tinit;
	}

	T[-1] = T1;
	T[N] = T2;

	for(t=0; t<time; t++) {
		if (t % printtime == 0) {
			printout(t, T, N);
		}
		v = T[-1];
		for(i=0; i<N; i++) {
			DT = k * (T[i+1] + v - 2*T[i]);
			v = T[i];
			T[i] += DT;
		}
	}
	printout(time, T, N);


	free(T-1);
	return 0;
}
