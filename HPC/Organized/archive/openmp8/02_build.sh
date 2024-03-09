gcc -O3 -lm -Wall -o pi_s pi.c -D IS_SERIAL
gcc -O3 -fopenmp -lm -Wall -o pi_p pi.c -D IS_PARALLEL