#include <iostream>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <mpi.h>

double my_custom_reduction(MPI_Comm communicator) {
    int processRank, numProcesses;
    MPI_Comm_rank(communicator, &processRank);
    MPI_Comm_size(communicator, &numProcesses);

    if (numProcesses < 2) {
        if (processRank == 0) {
            std::cerr << "Error: The number of processes must be at least 2." << std::endl;
        }
        return EXIT_FAILURE;
    }

    std::srand(std::time(0) + processRank);

    double localValue;

    if (processRank != 0) {
        localValue = static_cast<double>(std::rand()) / RAND_MAX;
        std::cout << "Process " << processRank << " has local value: " << localValue << std::endl;
    }

    double* allValues = new double[numProcesses];
    MPI_Request* sendRequests = new MPI_Request[numProcesses];

    if (processRank != 0) {
        MPI_Isend(&localValue, 1, MPI_DOUBLE, 0, 0, communicator, &sendRequests[processRank]);
    }

    if (processRank == 0) {
        for (int i = 1; i < numProcesses; ++i) {
            MPI_Irecv(&allValues[i], 1, MPI_DOUBLE, i, 0, communicator, &sendRequests[i]);
        }
    }
    double summedValue;
    MPI_Status recvStatus;
    int recvFlag;
    if (processRank == 0) {
        for (int i = 1; i < numProcesses; ++i) {
            do {
                MPI_Test(&sendRequests[i], &recvFlag, &recvStatus);
            } while (!recvFlag);
        }

        std::cout << "Received values at root process:" << std::endl;
        for (int i = 1; i < numProcesses; ++i) {
            std::cout << "Process " << i << ": " << allValues[i] << std::endl;
        }

        summedValue = std::accumulate(allValues + 1, allValues + numProcesses, 0.0);
        std::cout << "Summed value: " << summedValue << std::endl;
    }

    delete[] allValues;
    delete[] sendRequests;

    return summedValue;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    my_custom_reduction(MPI_COMM_WORLD);

    MPI_Finalize();

    return 0;
}
