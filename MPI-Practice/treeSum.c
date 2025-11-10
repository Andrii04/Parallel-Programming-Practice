#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool checkSendRecv(int rank, int step) {
    if ( (rank % (2*step)) == 0) return true; //receive
    else if ( ((rank % step) == 0) && ( rank % (2*step) != 0 ) ) return false; //send
}


int main(int argc, char** argv) {
    int step = 1; //level 0, step = 1
    int val = 2; //val each process holds
    int recvVal; //val to sum later

    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    while (step < size) {
        /*
        printf("current step: %d\n", step);
        printf("current rank: %d\n", rank);
        printf("rank-step: %d\n", rank-step);
        printf("rank+step: %d\n", rank+step);
        */

        if (checkSendRecv(rank, step)) {
            if (rank+step < size) {
            MPI_Recv(&recvVal, 1, MPI_INT, rank+step, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            val += recvVal;
            }
        }
        else {
            if (rank-step >= 0) {
            MPI_Send(&val, 1, MPI_INT, rank-step, 0, MPI_COMM_WORLD);
            }
        }
        step *= 2;
    }

    if (rank == 0) printf("total sum: %d\n", val);
    MPI_Finalize();
    return 0;
}
