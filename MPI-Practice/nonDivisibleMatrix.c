#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void createMatrix(int rows, int cols, int M[rows][cols]) {

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            M[i][j] = i;
        }
    }
}

void distributeRowsNDM(int rows, int cols, int M[rows][cols], int argc, char** argv) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int sendcounts[2] = {3*cols, 2*cols};
    int displsS[2] = {0, 3*cols};
    int recvcounts[2] = {1, 1};

    int localRow[sendcounts[rank]];
    int localRowSum = 0;
    int finalSumVector[size]; //perchè raccolgo 2 valori per processo (hanno più di 1 riga ciascun processo)

    MPI_Scatterv(M, sendcounts, displsS, MPI_INT, localRow, sendcounts[rank], MPI_INT, 0, MPI_COMM_WORLD);

    for (int i=0; i<sendcounts[rank]; i++) {
        localRowSum += localRow[i];
    }

    int displsG[2] = {0, 1};
    MPI_Gather(&localRowSum, 1, MPI_INT,
               finalSumVector, 1, MPI_INT,
               0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i=0; i<size; i++) {
            printf("elem %d: %d\n", i, finalSumVector[i]);
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int M[5][4];
    createMatrix(5, 4, M);
    distributeRowsNDM(5, 4, M, argc, argv);
    MPI_Finalize();
}