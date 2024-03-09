#!/bin/bash

for((N=10;N<=100000000;N*=10))
do
	sumsq=0
	for((i=0;i<16;i++))
	do
		err=`./omp_repi $N $i | tail -1 | cut -d' ' -f2`
		echo $N,$i,$err
	done
done
