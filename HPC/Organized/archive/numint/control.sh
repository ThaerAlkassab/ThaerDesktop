#!/bin/bash
for i in 10 100 1000 10000
do
	echo -en $i "\t"
	./numint.py $i |\
		cut -d' ' -f2 |\
		awk '{ORS="\t";print}'
	echo
done
