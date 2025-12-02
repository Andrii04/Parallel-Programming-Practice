#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrixPracticeMPI.c"

void matrixVectorProduct(int elems, int A[elems][elems], int V[elems], int argc, char** argv) {

    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int localRow[elems];
    int localRowSum = 0;
    int finalV[4];

    MPI_Scatter(A, 4, MPI_INT, localRow, 4, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i=0; i<4; i++) {
        localRowSum += (localRow[i] * V[i]);
    }

    MPI_Gather(&localRowSum, 1, MPI_INT, finalV, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i=0; i<4; i++) {
            printf("elem %d: %d\n", i, finalV[i]);
        }
    }

    MPI_Finalize();
}

int main(int argc, char** argv) {
    int A[4][4];
    int V[4] = {2, 3, 4, 1};
    createMatrix(4, 4, A);
    matrixVectorProduct(4, A, V, argc, argv);
    return 0;
}