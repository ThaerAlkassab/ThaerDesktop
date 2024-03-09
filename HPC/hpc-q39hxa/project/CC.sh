#!/bin/bash
#SBATCH --job-name=knapsack_job   # Specifies the name of the job
#SBATCH --nodes=1                 # Requests 1 node
#SBATCH --cpus-per-task=4         # Requests 4 CPU cores per task
#SBATCH --time=00:10:00           # Requests a time limit of 10 minutes

# Compile the C code with OpenMP support
gcc -fopenmp -o C_C_O C_C_O.c

# Run the compiled program using srun with 1 task
srun -n 1 ./C_C_O
