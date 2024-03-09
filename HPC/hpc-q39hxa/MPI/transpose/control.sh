#!/bin/bash
for((i=2;i<40000;i*=2)) # go over these numbers
do
	echo -en $i"\t"		# print i, -n: without \n, -e: needed for \t
	./transpose $i  | grep time | cut -d' ' -f3
		# call transpose with matrix size ixi
		# takes output containing 'time'
		# print 3rd value
	
#	echo	# we a new line
done
