#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=72
#SBATCH --time=00:10:00
#SBATCH --partition=s_hadoop,s_standard
#SBATCH --job-name=custom_reduction
#SBATCH --output=custom_reduction.out
#SBATCH --error=custom_reduction.err
module load mpi/openmpi/4.1.2-gcc-10.2.0

mpicxx -o custom_reduction.o custom_reduction.cpp 
mpiexec -n 7 ./custom_reduction.o