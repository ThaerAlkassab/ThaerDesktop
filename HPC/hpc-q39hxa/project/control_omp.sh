#!/bin/bash
for i in 10 100 1000 10000 100000 # go over these numbers
do
        echo -en $i"\t"         # print i, -n: without \n, -e: needed for \t
        ./C_C_S_omp $i  | awk '{ORS="\t";print }'
                # call C_C_S_omp with i subints
                # takes output line by line
                # prints 2nd columns ($2)
                # separates output with \t
                # ORS = output record separator

        echo    # we a new line
done
