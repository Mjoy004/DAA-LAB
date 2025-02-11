#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for a matrix
int** allocateMatrix(int size) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }
    return matrix;
}

// Function to free allocated memory
void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to add two matrices
void addMatrix(int** A, int** B, int** result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to subtract two matrices
void subtractMatrix(int** A, int** B, int** result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's matrix multiplication function
void strassenMultiply(int** A, int** B, int** C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    
    // Allocate memory for submatrices
    int** A11 = allocateMatrix(newSize);
    int** A12 = allocateMatrix(newSize);
    int** A21 = allocateMatrix(newSize);
    int** A22 = allocateMatrix(newSize);
    int** B11 = allocateMatrix(newSize);
    int** B12 = allocateMatrix(newSize);
    int** B21 = allocateMatrix(newSize);
    int** B22 = allocateMatrix(newSize);
    int** C11 = allocateMatrix(newSize);
    int** C12 = allocateMatrix(newSize);
    int** C21 = allocateMatrix(newSize);
    int** C22 = allocateMatrix(newSize);
    int** M1 = allocateMatrix(newSize);
    int** M2 = allocateMatrix(newSize);
    int** M3 = allocateMatrix(newSize);
    int** M4 = allocateMatrix(newSize);
    int** M5 = allocateMatrix(newSize);
    int** M6 = allocateMatrix(newSize);
    int** M7 = allocateMatrix(newSize);
    int** tempA = allocateMatrix(newSize);
    int** tempB = allocateMatrix(newSize);

    // Divide matrices into submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Compute M1 to M7
    addMatrix(A11, A22, tempA, newSize); 
    addMatrix(B11, B22, tempB, newSize); 
    strassenMultiply(tempA, tempB, M1, newSize); // M1 = (A11 + A22) * (B11 + B22)

    addMatrix(A21, A22, tempA, newSize); 
    strassenMultiply(tempA, B11, M2, newSize); // M2 = (A21 + A22) * B11

    subtractMatrix(B12, B22, tempB, newSize);
    strassenMultiply(A11, tempB, M3, newSize); // M3 = A11 * (B12 - B22)

    subtractMatrix(B21, B11, tempB, newSize);
    strassenMultiply(A22, tempB, M4, newSize); // M4 = A22 * (B21 - B11)

    addMatrix(A11, A12, tempA, newSize);
    strassenMultiply(tempA, B22, M5, newSize); // M5 = (A11 + A12) * B22

    subtractMatrix(A21, A11, tempA, newSize);
    addMatrix(B11, B12, tempB, newSize);
    strassenMultiply(tempA, tempB, M6, newSize); // M6 = (A21 - A11) * (B11 + B12)

    subtractMatrix(A12, A22, tempA, newSize);
    addMatrix(B21, B22, tempB, newSize);
    strassenMultiply(tempA, tempB, M7, newSize); // M7 = (A12 - A22) * (B21 + B22)

    // Compute C submatrices
    addMatrix(M1, M4, tempA, newSize);
    subtractMatrix(tempA, M5, tempB, newSize);
    addMatrix(tempB, M7, C11, newSize); // C11 = M1 + M4 - M5 + M7

    addMatrix(M3, M5, C12, newSize); // C12 = M3 + M5

    addMatrix(M2, M4, C21, newSize); // C21 = M2 + M4

    addMatrix(M1, M3, tempA, newSize);
    subtractMatrix(tempA, M2, tempB, newSize);
    addMatrix(tempB, M6, C22, newSize); // C22 = M1 + M3 - M2 + M6

    // Combine C submatrices into result
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Free allocated memory
    freeMatrix(A11, newSize); freeMatrix(A12, newSize); freeMatrix(A21, newSize); freeMatrix(A22, newSize);
    freeMatrix(B11, newSize); freeMatrix(B12, newSize); freeMatrix(B21, newSize); freeMatrix(B22, newSize);
    freeMatrix(C11, newSize); freeMatrix(C12, newSize); freeMatrix(C21, newSize); freeMatrix(C22, newSize);
    freeMatrix(M1, newSize); freeMatrix(M2, newSize); freeMatrix(M3, newSize); freeMatrix(M4, newSize);
    freeMatrix(M5, newSize); freeMatrix(M6, newSize); freeMatrix(M7, newSize);
    freeMatrix(tempA, newSize); freeMatrix(tempB, newSize);
}

// Driver Code to Test the Function
int main() {
    int size = 4;
    int** A = allocateMatrix(size);
    int** B = allocateMatrix(size);
    int** C = allocateMatrix(size);

    // Initialize matrices A and B with values
    // Call strassenMultiply(A, B, C, size);

    freeMatrix(A, size);
    freeMatrix(B, size);
    freeMatrix(C, size);

    return 0;
}
