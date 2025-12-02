#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int V[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

void distributeVector(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int localV[3];
    int finalV[12];
    MPI_Scatter(V, 3, MPI_INT, localV, 3, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i=0; i<3; i++) {
        localV[i] = localV[i]*2;
    }

    MPI_Gather(localV, 3, MPI_INT, finalV, 3, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (rank==0) {
        printf("final vector:\n");
        for (int i=0; i<12; i++) {
            printf("elem %d: %d\n", i, finalV[i]);
        }
    }

    MPI_Finalize();
}

void createMatrix(int rows, int cols, int M[rows][cols]) {

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            M[i][j] = i;
        }
    }
}

void distributeRows(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int M[4][4];
    createMatrix(4, 4, M);
    int row[4];
    int sumVector[4];

    MPI_Scatter(M, 4, MPI_INT, row, 4, MPI_INT, 0, MPI_COMM_WORLD);

    int localSum = 0;
    for (int i=0; i<4; i++) {
        localSum += row[i];
    }

    MPI_Gather(&localSum, 1, MPI_INT, sumVector, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i=0; i<4; i++) {
            printf("elem %d: %d\n", i, sumVector[i]);
        }
    }

    MPI_Finalize();
}

void matrixSum(int rows, int cols, int A[rows][cols], int B[rows][cols], int argc, char** argv) {

}
