#include <mpi.h>
#include <iostream>
#include <cassert>

int main(int argc, char** argv) {
  int l_ret = MPI_Init(&argc, &argv);
  assert(l_ret == MPI_SUCCESS);

  int rank, size;
  l_ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   assert(l_ret == MPI_SUCCESS);
  l_ret = MPI_Comm_size(MPI_COMM_WORLD, &size);
    assert(l_ret == MPI_SUCCESS);

    // Determine color
    int color = rank * 4 / size ;

    // Split the communicator based on color
    MPI_Comm new_comm;
    l_ret = MPI_Comm_split(MPI_COMM_WORLD, color, rank, &new_comm);
    assert(l_ret == MPI_SUCCESS);


    int  new_size;
    int new_rank;

  l_ret = MPI_Comm_size(new_comm, &new_size);
  assert(l_ret == MPI_SUCCESS);
  l_ret = MPI_Comm_rank(new_comm, &new_rank);
  assert(l_ret == MPI_SUCCESS);

  // Print information about the original and new communicators
  std::cout << "Rank " << rank << " out of " << size << " in MPI_COMM_WORLD, " \
            << "New Rank " << new_rank << " out of " << new_size << " in new_comm, " \
            << "Subgroup " << color << std::endl;


  l_ret = MPI_Comm_free(&new_comm);
  assert(l_ret == MPI_SUCCESS);

  l_ret = MPI_Finalize();
  assert(l_ret == MPI_SUCCESS);
  return EXIT_SUCCESS;
}