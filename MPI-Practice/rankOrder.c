#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank != 0) {
        int dummy;
        MPI_Recv(&dummy, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    printf("Hey I'm process %d\n", rank);
    fflush(stdout);

    if (rank < size-1) {
        int dummy = 0;
        MPI_Send(&dummy, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}