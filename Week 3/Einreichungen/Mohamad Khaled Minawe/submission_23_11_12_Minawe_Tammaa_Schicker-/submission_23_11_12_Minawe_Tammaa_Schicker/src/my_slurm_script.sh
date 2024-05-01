#!/bin/bash
#SBATCH --job-name=memory_bandwidth_test
#SBATCH --output=output.txt
#SBATCH --error=error.txt
#SBATCH --partition=s_hadoop
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=72
#SBATCH --time=1:00:00


# Set the email address where notifications should be sent.
#SBATCH --mail-user=minawe.mohamad.khaled@uni-jena.de

# Specify the types of email notifications you want to receive.
#SBATCH --mail-type=BEGIN,END,FAIL

# Load modules 


module load tools/python/3.8
pip install pandas matplotlib

CXX=g++
CXXFLAGS="-O -march=native -std=c++11" 
OUTPUT_FILE=memory_bandwidth.o
$CXX $CXXFLAGS -o $OUTPUT_FILE Benchmarking.cpp
./$OUTPUT_FILE
python plotter.py






