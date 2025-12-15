// main.cpp
#include <iostream>
#include "StrassenOptimizer.h"
#include "CacheMatrix.h"

// Need to declare THRESHOLD here again since it's used as 'extern' in the header
extern int THRESHOLD; 

int main() {
    std::cout << "Starting Cache-Optimized Adaptive Strassen Multiplier project.\n";

    // Step 1: Run the unique adaptive benchmark
    run_benchmarks_to_set_threshold();

    // Step 2: Test with a large matrix (must be power of 2 for this basic implementation)
    const int N = 128; 
    CacheMatrix A(N);
    CacheMatrix B(N);

    // Initialize A and B with some values (e.g., random data)
    for(int i = 0; i < N*N; ++i) {
        A.data[i] = i * 0.1;
        B.data[i] = i * 0.2;
    }

    std::cout << "\nMultiplying " << N << "x" << N << " matrices using optimized Strassen/Standard hybrid...\n";
    
    // Step 3: Perform the optimized multiplication
    CacheMatrix C = multiply_strassen_optimized(A, B);

    std::cout << "Multiplication complete. Result matrix C calculated.\n";
    // You can add logic here to print a small part of C to verify.

    return 0;
}
