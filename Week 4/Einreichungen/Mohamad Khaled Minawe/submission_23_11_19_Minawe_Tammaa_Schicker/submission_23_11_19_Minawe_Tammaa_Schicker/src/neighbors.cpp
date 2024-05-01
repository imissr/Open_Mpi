#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        std::cerr << "\u001B[31mAt least two processes !!" << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    int message = 69;
    MPI_Status status;

    if (rank == 0) {
        std::cout << "\u001B[32m-> Process " << rank << " ,sends Message : " << message << " to process " << rank + 1 << std::endl;
        MPI_Send(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        std::cout << "\u001B[33m<- Process " << rank << ": Received the Message " << message << " from process " << rank - 1 << std::endl;

        if (rank != size - 1) {
            std::cout << "\u001B[32m-> The Process " << rank << ": ,sends Message " << message << " to process " << rank + 1 << std::endl;
            MPI_Send(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        } else {
            message += rank;
            std::cout << "\u001B[34m!! Process " << rank << ": adds its Rank to the Message -> " << message << " then sends it back to process 0" << std::endl;
            MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();

    return 0;
}
