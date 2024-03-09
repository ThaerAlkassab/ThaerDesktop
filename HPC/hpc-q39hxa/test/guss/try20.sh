#!/bin/bash

# Function to run NGUT and extract the number of guesses
function run_NGUT_and_print_output {
    mpirun -n 2 ./NGUT
}

# Run NGUT to get the number of tries
tries=$(run_NGUT_and_print_output | grep tries | cut -d' ' -f5)
echo "Number of tries: $tries"

# Array to store the number of guesses
declare -a guesses_array=()

# Loop to run NGUT 20 times and get the number of guesses
for ((i=0; i<20; i++)); do
    guesses=$(run_NGUT_and_print_output | grep "Correct guess" | wc -l)
    echo "Guesses for Try $((i+1)): $guesses"
    guesses_array+=("$guesses")
done

# Calculate the mean
mean=$(printf '%s\n' "${guesses_array[@]}" | awk '{ total += $1 } END { if (NR > 0) print total/NR }')
echo "Average of guesses: $mean"
