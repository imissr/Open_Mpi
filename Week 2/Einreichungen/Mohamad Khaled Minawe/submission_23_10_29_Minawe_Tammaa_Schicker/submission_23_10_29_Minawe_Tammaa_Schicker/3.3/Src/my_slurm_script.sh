#!/bin/bash
#SBATCH --job-name=fibonacci
#SBATCH --output=output.txt
#SBATCH --error=error.txt
#SBATCH --partition=s_hadoop
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --time=00:10:00


# Set the email address where notifications should be sent.
#SBATCH --mail-user=minawe.mohamad.khaled@uni-jena.de

# Specify the types of email notifications you want to receive.
#SBATCH --mail-type=BEGIN,END,FAIL


start_time=$(date +%s)


# Enter your executable commands here
g++ fibonacci.cpp



# Execute the compiled program
./a.out
end_time=$(date +%s)

elapsed_time=$((end_time - start_time))

echo "Start Time: $start_time" >> output.txt
echo "End Time: $end_time" >> output.txt
echo "Elapsed Time: $elapsed_time seconds" >> output.txt



