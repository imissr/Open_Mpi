#!/bin/bash
#SBATCH --job-name=mpitree
#SBATCH --output=mpitree_output.txt
#SBATCH --error=mpitree_error.txt
#SBATCH --partition=s_hadoop
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --time=10:00
#SBATCH --cpus-per-task=72


# Set the email address where notifications should be sent.
#SBATCH --mail-user=minawe.mohamad.khaled@uni-jena.de

# Specify the types of email notifications you want to receive.
#SBATCH --mail-type=BEGIN,END,FAIL

# Load modules 

module load mpi/openmpi/4.1.2-gcc-10.2.0

date
mpicxx -o tree_broadcast.o treeboardcast.cpp
mpirun -np 50 -oversubscribe ./tree_broadcast.o 100000000





