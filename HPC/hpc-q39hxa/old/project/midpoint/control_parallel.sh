#!/bin/bash
for i in 10 100 1000 10000 100000 1000000 10000000 100000000 1000000000 # go over these numbers
do
        echo -en $i"\t"         # print i, -n: without \n, -e: needed for \t
        ./gauss_parallel $i  | awk '{ORS="\t";print $2}'
                # call numint.py with i subints
                # takes output line by line
                # prints 2nd columns ($2)
                # separates output with \t
                # ORS = output record separator

        echo    # we a new line
done
