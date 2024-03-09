#!/bin/bash 
hn=$(hostname)
cpuid=$(cat /proc/cpuinfo | grep processor | wc -l)
printf "Hello World from %s CPU %s\n" "$hn" "$cpuid"