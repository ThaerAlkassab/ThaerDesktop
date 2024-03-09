#!/bin/bash
echo -n "" > res_s.txt
for i in 10 100 1000 10000 100000 1000000
do
	echo -en $i "\t" >> res_s.txt
	./numint_s $i >> res_s.txt
done

#!/bin/bash
echo -n "" > res_p.txt
for i in 10 100 1000 10000 100000 1000000
do
	echo -en $i "\t" >> res_p.txt
	OMP_NUM_THREADS=10 ./numint_p $i >> res_p.txt
done
