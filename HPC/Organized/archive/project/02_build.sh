gcc -O3 -lm -Wall -o 01_bifurcation_s 01_bifurcation.c -D IS_SERIAL
gcc -O3 -fopenmp -lm -Wall -o 01_bifurcation_p 01_bifurcation.c -D IS_PARALLEL