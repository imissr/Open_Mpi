// fibonacci rec.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdio>


unsigned int fibo(unsigned n) {
    if (n < 2) {
        return n;
    }
    else {
        return fibo(n - 1) + fibo(n - 2);
    }
}

int main()
{      
    for (size_t i = 0; i < 100; i++)
    {

        unsigned int n;


        std::cout << "fibonacci number" << i << ": " << fibo(i) << std :: endl; 

    }
    
}



