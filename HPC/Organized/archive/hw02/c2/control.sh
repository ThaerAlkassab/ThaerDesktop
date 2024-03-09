#!/bin/bash
echo -n "" > res.txt
for i in 10 100 1000 10000
do
	echo -en $i "\t" >> res.txt
	./numint $i >> res.txt
done
