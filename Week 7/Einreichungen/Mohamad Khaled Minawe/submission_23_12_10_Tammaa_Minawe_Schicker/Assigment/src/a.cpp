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

    char data[50] = "hi there";

    

  l_ret = MPI_Win_create(&data[0], sizeof(data)*50 ,sizeof(char) , MPI_INFO_NULL,
                          MPI_COMM_WORLD, &win);
  assert(l_ret == MPI_SUCCESS);


  l_ret = MPI_Win_fence(0,win);
  assert(l_ret == MPI_SUCCESS);

  if(rank == 1 ){
  l_ret = MPI_Put(&data[0],0, MPI_CHAR,0, sizeof(char),0, MPI_CHAR,win);
  assert(l_ret == MPI_SUCCESS);
  }

  l_ret = MPI_Win_fence(0, win);
  assert(l_ret == MPI_SUCCESS);


  if(rank == 0){
    std::cout << "data: " << data << std::endl;
  }

  l_ret = MPI_Win_free(&win);
  assert(l_ret == MPI_SUCCESS);

  l_ret = MPI_Finalize();
  assert(l_ret == MPI_SUCCESS);

 
 
  
  return EXIT_SUCCESS;
}