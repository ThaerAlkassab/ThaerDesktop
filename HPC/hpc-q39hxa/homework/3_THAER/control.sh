#!/bin/bash
for i in 10 100 1000 10000 100000 1000000 10000000 # go over these numbers
do
	echo -en $i"\t"		# print i, -n: without \n, -e: needed for \t
	mpirun -n 4 NUMINT_MPI $i  | awk '{ORS="\t";print $2}'
	echo	# we a new line
done