#include <mpi.h>
#include <assert.h>
#include <stdio.h>

int GeneralPassive(int argc, char *argv[])
{
    if(MPI_Init(&argc, &argv) != MPI_SUCCESS) return -1;

    int l_rank,l_c_size;

    if(MPI_Comm_rank(MPI_COMM_WORLD, &l_rank) != MPI_SUCCESS) return -1;
    if(MPI_Comm_size(MPI_COMM_WORLD, &l_c_size)!= MPI_SUCCESS) return -1;

    double *buffer = new double[l_c_size];
    buffer[0] = l_rank * 10; 

    MPI_Win l_window;

    if(MPI_Win_create(buffer, l_c_size * sizeof(double), sizeof(double), MPI_INFO_NULL, MPI_COMM_WORLD, &l_window)!= MPI_SUCCESS) return -1;
    
    if(l_rank != 0){
        if(MPI_Win_lock( MPI_LOCK_SHARED, 0, 0, l_window)!= MPI_SUCCESS) return -1;
        if(MPI_Put(buffer,1,MPI_DOUBLE,0,l_rank,1,MPI_DOUBLE, l_window)!= MPI_SUCCESS) return -1;
        if(MPI_Win_unlock(0, l_window)!= MPI_SUCCESS) return -1;
    }

    if (l_rank == 0)
    {
        std::cout << "buffer_data : " << std::endl;
        for (int i = 0; i < l_c_size; i++)
        {
            std::cout << i << " -> " << buffer[i] << std::endl;
        }
    }

    MPI_Win_free(&l_window);
    MPI_Finalize();
    delete[] buffer;

    return 0;
}

int GeneralActive(int argc, char *argv[])
{
    if(MPI_Init(&argc, &argv) != MPI_SUCCESS) return -1;

    int l_rank,l_c_size;

    if(MPI_Comm_rank(MPI_COMM_WORLD, &l_rank) != MPI_SUCCESS) return -1;
    if(MPI_Comm_size(MPI_COMM_WORLD, &l_c_size)!= MPI_SUCCESS) return -1;

    size_t l_buffer_size = 0;
    if(l_rank == 0){
        l_buffer_size = l_c_size * sizeof(double);
    }else{
        l_buffer_size = sizeof(double);
    }
    double *buffer = new double[l_buffer_size];
    buffer[0] = l_rank * 10; 

    MPI_Win l_window;

    if(MPI_Win_create(buffer, l_buffer_size, sizeof(double), MPI_INFO_NULL, MPI_COMM_WORLD, &l_window)!= MPI_SUCCESS) return -1;
    if(MPI_Win_fence(0, l_window)!= MPI_SUCCESS) return -1;
    if (l_rank != 0)
    {
        if(MPI_Put(buffer, 1, MPI_DOUBLE, 0, l_rank, 1, MPI_DOUBLE, l_window)!= MPI_SUCCESS) return -1;
    }
    if(MPI_Win_fence(0, l_window)!= MPI_SUCCESS) return -1;

    if (l_rank == 0)
    {
        std::cout << "buffer_data : " << std::endl;
        for (int i = 0; i < l_c_size; i++)
        {
            std::cout << i << " -> " << buffer[i] << std::endl;
        }
    }

    MPI_Win_free(&l_window);
    MPI_Finalize();
    delete[] buffer;

    return 0;
}

int main(int argc, char *argv[])
{
    int l_status = 0;
    
    l_status = GeneralPassive(argc, argv);
    //l_status = GeneralActive(argc, argv);

    if(l_status != 0){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}