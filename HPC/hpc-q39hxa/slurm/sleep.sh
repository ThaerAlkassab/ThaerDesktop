#!/bin/bash
#!SBATCH --job-name=sleeper
#!SBATCH --ntasks=1
#!SBATCH --mem=1gb
#!SBATCH --time=00:05:00
#!SBATCH --output=slurm_%j_%x.out
#!SBATCH --error=slurm_%j_%x.out

pwd
hostname
date
echo "Sleeping"
sleep 60 # sleep one minute
date