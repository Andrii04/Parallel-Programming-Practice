#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    int rank, size;
    int total_tosses, local_tosses;
    int total_in_circle, local_in_circle;
    int x, y;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    
    total_tosses = 10;
    local_in_circle = 0;

    printf("Hey I'm Process %d!\n", rank);

    if (rank != 0) {
        local_tosses = total_tosses / size;
        srand(time(NULL) + rank);
        for (int i=0; i<local_tosses; i++) {
            
            double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
            double y = (double)rand() / RAND_MAX * 2.0 - 1.0;

            printf("toss %d:\nx = %lf\ny = %lf\n", i+1, x, y);
            if ((x*x + y*y) <= 1) {
                local_in_circle++;
                printf("In Circle! Yay!\n");
            }
            else printf("Not In Circle... Nay...\n");
        }
    }
    MPI_Reduce(&local_in_circle, &total_in_circle, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    printf("\n");
    if (rank == 0) {
        double pi_estimate = 4 * total_in_circle / ( (double) total_tosses);
        printf("pi_estimate = %lf\n", pi_estimate);
    }

    MPI_Finalize();
    return 0;
}
