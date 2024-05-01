#include <iostream>
#include <random>
#include <mpi.h>
#include <chrono>
#include <cassert>

void tree_broadcast(double *data, int count, int size, int rank){
    int root = size / 2 ;

    if(rank == root){
        MPI_Send(data, count, MPI_DOUBLE, root - 1, 0, MPI_COMM_WORLD);
        MPI_Send(data, count, MPI_DOUBLE, root + 1, 0, MPI_COMM_WORLD);
    }else if (rank > root){
        MPI_Recv(data, count, MPI_DOUBLE, rank - 1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(rank < size-1){
            MPI_Send(data, count, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD);
        }
    }else{
        MPI_Recv(data, count, MPI_DOUBLE, rank + 1 , MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(rank > 0){
            MPI_Send(data, count, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD);
        }
    }


}

int main(int argc, char *argv[]) {

    int l_ret = MPI_Init(&argc, &argv);
    assert(l_ret == MPI_SUCCESS);

    int l_rank;
    int l_comm_size;

    l_ret= MPI_Comm_rank(MPI_COMM_WORLD, &l_rank);
    assert(l_ret == MPI_SUCCESS);
    l_ret = MPI_Comm_size(MPI_COMM_WORLD, &l_comm_size);
    assert(l_ret == MPI_SUCCESS);

    if (argc != 2) {
        printf("Usage: %s <size>\n", argv[0]);
        return 1;
    }

    int number = atoi(argv[1]);

    if (number <= 0) {
        printf("Please enter a positive integer for the size.\n");
        return 1;
    }


    // Create a random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);  // Adjust the range if needed

    // Dynamically allocate memory for the array
    double *myArray = new double[number];

    // Initialize the array elements with random numbers
    for (int i = 0; i < number; ++i) {
        myArray[i] = distribution(gen);
    }


    auto start = std::chrono::high_resolution_clock::now();
    tree_broadcast(myArray, number, l_comm_size,l_rank);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    if (l_rank == l_comm_size / 2)
    {
        std::cout << "tree_bordcast: Processes: " << l_comm_size << " number of elements: "
         << number << " time: " << elapsed.count() << " seconds" << std::endl;
    }

   /* // Display the initialized array
    std::cout << "Initialized array with " << N << " elements:" << std::endl;
    for (int i = 0; i < number; ++i) {
        std::cout << myArray[i] << " ";
    }
    std::cout << std::endl;*/


    start = std::chrono::high_resolution_clock::now();
    MPI_Bcast(myArray, number, MPI_DOUBLE, l_comm_size / 2, MPI_COMM_WORLD);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    if (l_rank == l_comm_size / 2)
    {
        std::cout << "MPI_Bcast: Processes: " << l_comm_size << " number of elements: " << number << " time: "
         << elapsed.count() << " seconds" << std::endl;
    }


    // Don't forget to free the dynamically allocated memory
    delete[] myArray;

    l_ret = MPI_Finalize();
    assert(l_ret == MPI_SUCCESS);

     return EXIT_SUCCESS;
}

