#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double get_rand_minus_one_one()
{
    return 2 * (rand() / (double)RAND_MAX) - 1;
}

int main(int argc, char **argv)
{
    int rank, size;
    int num_tosses = atoi(argv[1]);
    int local_tosses;
    int num_hits, local_in_circle;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank);
    local_in_circle = 0;

    local_tosses = num_tosses / size;
    for (int i = 0; i < local_tosses; i++)
    {

        double x = get_rand_minus_one_one();
        double y = get_rand_minus_one_one();

        if ((x * x + y * y) <= 1)
        {
            local_in_circle++;
        }
    }

    MPI_Reduce(&local_in_circle, &num_hits, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    printf("\n");
    if (rank == 0)
    {
        double pi_estimate = 4 * num_hits / ((double)num_tosses);
        printf("Estimate of pi = %f\n", pi_estimate);
    }

    MPI_Finalize();
    return 0;
}