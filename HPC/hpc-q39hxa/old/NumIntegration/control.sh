for i in 10 100 1000 10000
do
	echo -en $i"\t"
	./numint.py $i | \
		awk " {ORS="\t";print $2}"
	echo
done