#include <stdio.h>
#include <pthread.h>

#define SIZE 3

int A[SIZE][SIZE] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

int B[SIZE][SIZE] = {
    {9, 8, 7},
    {6, 5, 4},
    {3, 2, 1}
};

int C[SIZE][SIZE]; // Result matrix

// Thread function to compute one row
void* multiplyRow(void* arg) {
    int row = *(int*)arg;
    for (int col = 0; col < SIZE; col++) {
        C[row][col] = 0;
        for (int k = 0; k < SIZE; k++) {
            C[row][col] += A[row][k] * B[k][col];
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[SIZE];
    int row_indices[SIZE];

    // Create threads
    for (int i = 0; i < SIZE; i++) {
        row_indices[i] = i;
        pthread_create(&threads[i], NULL, multiplyRow, (void*)&row_indices[i]);
    }

    // Join threads
    for (int i = 0; i < SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print result
    printf("Resultant Matrix C = A x B:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%4d", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
