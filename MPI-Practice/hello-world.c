#include <stdio.h>
#include <mpi.h>
#include <string.h>

const int MAX_STRING=100;

int main(void){

    int size, rank;
    char stringa[MAX_STRING];
    MPI_Init(NULL, NULL);
    
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if (rank!=0){

        sprintf(stringa, "Hello, World! I am process %d of %d.", rank,size);
        MPI_Send(stringa,strlen(stringa)+1,MPI_CHAR,0,0,MPI_COMM_WORLD);

    }else{

        printf("Hello, World! I am process %d of %d.\n", rank, size);

        for(int q=1;q<size;q++){

            MPI_Recv(stringa, MAX_STRING ,MPI_CHAR,q,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            printf("%s\n", stringa);

        }
    }

    MPI_Finalize();
    return 0;
}
