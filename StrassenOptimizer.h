// StrassenOptimizer.h
#ifndef STRASSEN_OPTIMIZER_H
#define STRASSEN_OPTIMIZER_H

#include "CacheMatrix.h"

// Dynamically determined base case threshold
extern int THRESHOLD; 

CacheMatrix multiply_standard(const CacheMatrix& A, const CacheMatrix& B);
CacheMatrix multiply_strassen_optimized(const CacheMatrix& A, const CacheMatrix& B);
void run_benchmarks_to_set_threshold();

#endif // STRASSEN_OPTIMIZER_H
