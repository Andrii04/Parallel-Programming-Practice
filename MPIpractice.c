#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int ranking, size;

    //Inizializiamo l'ambiente MPI
    MPI_Init(&argc, &argv);

    //Ottengo n tot processi
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Ottengo rank(ID) del processo corrente
    MPI_Comm_rank(MPI_COMM_WORLD, &ranking);

    printf("Processo: %d su %d\n", ranking, size);

    MPI_Finalize();
    return 0;
}

