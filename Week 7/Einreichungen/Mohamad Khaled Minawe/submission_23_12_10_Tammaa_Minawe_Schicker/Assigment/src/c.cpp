#include <mpi.h>
#include <iostream>
#include <cassert>
#include <cstring>

int main(int argc, char** argv) {
  int l_ret = MPI_Init(&argc, &argv);
  assert(l_ret == MPI_SUCCESS);

  int rank, size ;
  MPI_Win win;
  
  l_ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   assert(l_ret == MPI_SUCCESS);
  l_ret = MPI_Comm_size(MPI_COMM_WORLD, &size);
    assert(l_ret == MPI_SUCCESS);

    char data1[50] = "hi there";
    char data2[50] = "How are you";

  

  l_ret = MPI_Win_create(&data1[0], sizeof(data1)*50 ,sizeof(char) , MPI_INFO_NULL,
                          MPI_COMM_WORLD, &win);
  assert(l_ret == MPI_SUCCESS);


  l_ret = MPI_Win_fence(0,win);
  assert(l_ret == MPI_SUCCESS);

  int targetRank = (rank + 1) % size; 

  MPI_Put(&data1[0], sizeof(data1) , MPI_CHAR, targetRank, 0, sizeof(data1), MPI_CHAR, win);

  l_ret = MPI_Win_fence(0, win);
  assert(l_ret == MPI_SUCCESS);

  printf("Process %d received: %s\n", rank, data1);

  targetRank = (rank + size - 1) % size;
  MPI_Put(&data2[0], sizeof(data2) + 1, MPI_CHAR, targetRank, 0, sizeof(data2), MPI_CHAR, win);


  printf("Process %d received: %s\n", rank, data2);
 

  l_ret = MPI_Win_free(&win);
  assert(l_ret == MPI_SUCCESS);

  l_ret = MPI_Finalize();
  assert(l_ret == MPI_SUCCESS);

 
 
  return EXIT_SUCCESS;
}