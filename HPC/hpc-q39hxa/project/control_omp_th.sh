#!/bin/bash
#SBATCH --job-name=project_mesure
#SBATCH -n 1
#SBATCH -c 32
#SBATCH -o %x_%j.out
#SBATCH -e %x_%j.err


#OMP mesure
for p in 1 2 4 8 16 32 64 128
do
    echo -en $p "\n"
    OMP_NUM_THREADS=$p srun -c 12 ./control_omp.sh
  echo -en "\n"
done
