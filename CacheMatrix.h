// CacheMatrix.h
#ifndef CACHE_MATRIX_H
#define CACHE_MATRIX_H

#include <vector>
#include <iostream>
#include <algorithm>

class CacheMatrix {
public:
    int size;
    // Use a single vector for contiguous memory allocation
    std::vector<double> data; 

    // Constructor
    CacheMatrix(int n) : size(n), data(n * n, 0.0) {}

    // Method to get a sub-matrix view (efficient, doesn't copy data)
    CacheMatrix get_submatrix(int row_start, int col_start, int sub_size) const {
        // This is a simplified view creation idea, in a real system you'd use pointers 
        // or smart indexing to avoid copying data during recursion. 
        // For simple implementation, we return a copy here:
        CacheMatrix sub(sub_size);
        for (int i = 0; i < sub_size; ++i) {
            for (int j = 0; j < sub_size; ++j) {
                sub.data[i * sub_size + j] = this->data[(row_start + i) * this->size + (col_start + j)];
            }
        }
        return sub;
    }
};

#endif // CACHE_MATRIX_H
