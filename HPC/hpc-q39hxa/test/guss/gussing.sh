#! /bin/bash

typeset -i c=0

inp=-1

((gen=RANDOM%100+1))

while((gen!=inp))
do
	echo
	read -p "Enter your guss     " inp
	echo
	((c++))
	if((inp<gen));then
		echo -e "\nYour guss is too low\n";
	elif((inp>guss));then
		echo -e "\nYour guss is too high\n";
	fi
done
echo -e '\nSuccessfully Gussed\n';
