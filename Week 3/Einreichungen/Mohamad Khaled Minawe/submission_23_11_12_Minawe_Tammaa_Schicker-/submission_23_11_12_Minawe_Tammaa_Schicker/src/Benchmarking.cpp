#include <iostream>
#include <chrono>
#include <fstream>

int main() {

    const int array_sizes[30] = {10,50,70,100,300,500,1000,3000,5000,8000,9000,
        10000,12500,30000,40000,50000,75000,80000,100000,200000,300000,400000,500000,800000,900000,
        1000000,2000000,3000000,4000000,5000000};
    const int sizes = sizeof(array_sizes) / sizeof(array_sizes[0]);
    double scalar = 2.0;
    std::ofstream csv_file("memory_bandwidth.csv");
    csv_file << "Array Size (bytes),Bandwidth (GB/s)\n";
    const int num_iterations = 10000;

    for (int size_idx = 0; size_idx < sizes; ++size_idx) {
        const int array_size = array_sizes[size_idx];
        double* array_A = new double[array_size];
        double* array_B = new double[array_size];
        double* array_C = new double[array_size];

        for (int i = 0; i < array_size; ++i) {
            array_A[i] = static_cast<double>(std::rand()) / RAND_MAX;
            array_B[i] = static_cast<double>(std::rand()) / RAND_MAX;
            array_C[i] = 0.0;
        }
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int iteration = 0; iteration < num_iterations; ++iteration) {
            for (int i = 0; i < array_size; ++i) {
                array_C[i] = array_A[i] + scalar * array_B[i];
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double,std::milli> duration = end_time - start_time;
        double data_access_speed =  num_iterations * 3.0 * array_size * sizeof(double) / (duration.count()/1000) / (1024 * 1024 * 1024);
        csv_file << array_sizes[size_idx] * 3 * sizeof(double) << "," << data_access_speed << "\n";

        delete[] array_A;
        delete[] array_B;
        delete[] array_C;
    }
    csv_file.close();
    std::cout << "We've stored the memory bandwidth measurements in the memory_bandwidth.csv file." << std::endl;
    return 0;
}
