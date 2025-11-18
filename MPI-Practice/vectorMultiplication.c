#include <mpi.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Multiplication vector-scalar and vector-vector for dot product
// first we multiply vector1 for scalar (result1)
// then we get the sum1 of vector1 and sum2 of vector2, and then multiply sum1 by sum2 (result2)
// print both result1 and result2

int V1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int V2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
int S = 2;

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int lenV = 10;
    int localVlen = lenV/size;

    int localV1[localVlen];
    int localV2[localVlen];
    int multipliedLocalV[localVlen];
    int finalV[10];

    int localDot = 0;
    int totalDot = 0;

    MPI_Scatter(V1, 2, MPI_INT, localV1, 2, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(V2, 2, MPI_INT, localV2, 2, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i=0; i<localVlen; i++) {
        multipliedLocalV[i] = localV1[i] * S;
        localDot += (localV1[i] * localV2[i]);
    }

    MPI_Gather(multipliedLocalV, 2, MPI_INT, finalV, 2, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Reduce(&localDot, &totalDot, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("multiplied Vector:\n");
        for (int i=0; i<lenV; i++) {
            printf("idx %d: %d\n", i, finalV[i]);
        }
        printf("\ndot product: %d\n", totalDot);
    }

    MPI_Finalize();
    return 0;
}