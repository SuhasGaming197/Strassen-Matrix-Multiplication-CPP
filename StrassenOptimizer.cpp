// StrassenOptimizer.cpp
#include "StrassenOptimizer.h"
#include <cmath>
#include <iostream>

// Global variable for the adaptive threshold
int THRESHOLD = 0; 

// --- Helper Functions (Simplified for demonstration) ---

CacheMatrix add(const CacheMatrix& A, const CacheMatrix& B) {
    int n = A.size;
    CacheMatrix C(n);
    for (int i = 0; i < n * n; ++i) C.data[i] = A.data[i] + B.data[i];
    return C;
}

CacheMatrix subtract(const CacheMatrix& A, const CacheMatrix& B) {
    int n = A.size;
    CacheMatrix C(n);
    for (int i = 0; i < n * n; ++i) C.data[i] = A.data[i] - B.data[i];
    return C;
}

// --- Standard O(N^3) Multiplication (Base Case) ---

CacheMatrix multiply_standard(const CacheMatrix& A, const CacheMatrix& B) {
    int n = A.size;
    CacheMatrix C(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0.0;
            for (int k = 0; k < n; ++k) {
                sum += A.data[i * n + k] * B.data[k * n + j];
            }
            C.data[i * n + j] = sum;
        }
    }
    return C;
}

// --- Optimized Strassen Algorithm (Recursive) ---

CacheMatrix multiply_strassen_optimized(const CacheMatrix& A, const CacheMatrix& B) {
    int n = A.size;

    // *** THE ADAPTIVE THRESHOLD SWITCH ***
    if (n <= THRESHOLD) {
        return multiply_standard(A, B);
    }

    int m = n / 2;
    // Note: In a true cache-optimized implementation, these 'get_submatrix' 
    // calls would use memory views/pointers rather than copying data into new CacheMatrix objects.

    CacheMatrix a11 = A.get_submatrix(0, 0, m);
    CacheMatrix a12 = A.get_submatrix(0, m, m);
    CacheMatrix a21 = A.get_submatrix(m, 0, m);
    CacheMatrix a22 = A.get_submatrix(m, m, m);
    CacheMatrix b11 = B.get_submatrix(0, 0, m);
    CacheMatrix b12 = B.get_submatrix(0, m, m);
    CacheMatrix b21 = B.get_submatrix(m, 0, m);
    CacheMatrix b22 = B.get_submatrix(m, m, m);

    // Strassen formulas (P1 to P7 recursive calls)
    CacheMatrix p1 = multiply_strassen_optimized(add(a11, a22), add(b11, b22));
    CacheMatrix p2 = multiply_strassen_optimized(add(a21, a22), b11);
    CacheMatrix p3 = multiply_strassen_optimized(a11, subtract(b12, b22));
    CacheMatrix p4 = multiply_strassen_optimized(a22, subtract(b21, b11));
    CacheMatrix p5 = multiply_strassen_optimized(add(a11, a12), b22);
    CacheMatrix p6 = multiply_strassen_optimized(subtract(a21, a11), add(b11, b12));
    CacheMatrix p7 = multiply_strassen_optimized(subtract(a12, a22), add(b21, b22));

    // Combine products to get resulting quadrants
    CacheMatrix c11 = add(subtract(add(p1, p4), p5), p7);
    CacheMatrix c12 = add(p3, p5);
    CacheMatrix c21 = add(p2, p4);
    CacheMatrix c22 = add(subtract(add(p1, p3), p2), p6);

    // This part requires copying the quadrants back into one large matrix 'C' of size n
    CacheMatrix C(n);
    // Code to reassemble C from c11, c12, etc... 
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            C.data[i * n + j] = c11.data[i * m + j];
            C.data[i * n + j + m] = c12.data[i * m + j];
            C.data[(i + m) * n + j] = c21.data[i * m + j];
            C.data[(i + m) * n + j + m] = c22.data[i * m + j];
        }
    }

    return C;
}

// Function defined in Benchmarks.cpp (implicitly called here for simplicity)
void run_benchmarks_to_set_threshold() {
    // In the full implementation, this function would run standard vs. strassen 
    // timing tests for N=2, 4, 8, 16, 32, 64, 128... and set the optimal THRESHOLD value.
    std::cout << "Running benchmarks to find optimal threshold for this CPU...\n";
    // For now, we manually set a common threshold:
    THRESHOLD = 64; 
    std::cout << "Threshold set to N=" << THRESHOLD << ".\n";
}
