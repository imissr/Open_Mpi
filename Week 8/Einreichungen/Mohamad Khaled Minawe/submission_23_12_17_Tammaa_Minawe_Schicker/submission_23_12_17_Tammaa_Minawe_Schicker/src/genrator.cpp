#include <mpi.h>
#include <assert.h>
#include <stdio.h>
#include <random>
#include <iostream>
#include <chrono>


int main(int argc, char** argv) {
  int l_ret = MPI_Init(&argc, &argv);
  assert(l_ret == MPI_SUCCESS);

  int rank, size ;
  MPI_Win win;
  
  l_ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   assert(l_ret == MPI_SUCCESS);
  l_ret = MPI_Comm_size(MPI_COMM_WORLD, &size);
    assert(l_ret == MPI_SUCCESS);


    std::mt19937_64 rng(rank);  // Each process has its own seed based on its rank
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    const long long total_samples = 50000000;
    long long samples_per_process = total_samples / size;

    
    long long local_inside_circle = 0;
    long long global_inside_circle;
    
    auto start_time = std::chrono::high_resolution_clock::now();

     for (long long i = 0; i < samples_per_process; ++i) {
        double x = dist(rng);
        double y = dist(rng);
        double distance_squared = x * x + y * y;
        if (distance_squared <= 1.0) {
            local_inside_circle++;
        }
    }


      l_ret = MPI_Reduce(&local_inside_circle, &global_inside_circle, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
      assert(l_ret == MPI_SUCCESS);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();



 

       if (rank == 0) {
        double pi_estimate = (4.0 * global_inside_circle) / total_samples;
        double error = std::abs(pi_estimate - M_PI);

        std::cout << "Estimated Pi: " << pi_estimate << std::endl;
        std::cout << "Error: " << error << std::endl;
        std::cout << "Time-to-solution: " << elapsed_time << " milliseconds" << std::endl;
    }
   

    MPI_Finalize();
   assert(l_ret == MPI_SUCCESS);

 
 
  
  return EXIT_SUCCESS;
}