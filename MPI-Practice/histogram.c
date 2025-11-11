#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Usage (run on any rank count):
 *   ./histogram <data_count> <bin_count> <min_meas> <max_meas> v1 v2 ... vN
 * where N == data_count and all v* are floats.
 *
 * Rank 0 reads the args and distributes data to other ranks using MPI_Scatterv
 * so arbitrary data_count (not necessarily divisible by number of processes)
 * is supported.
 */

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data_count = 0;
    int bin_count = 0;
    float min_meas = 0.0f, max_meas = 0.0f;
    float *data = NULL; /* only rank 0 will fill this */

    /* Rank 0 parses command-line arguments */
    if (rank == 0) {
        if (argc < 5) {
            fprintf(stderr, "Usage: %s data_count bin_count min_meas max_meas v1 v2 ... vN\n", argv[0]);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        data_count = atoi(argv[1]);
        bin_count = atoi(argv[2]);
        min_meas = atof(argv[3]);
        max_meas = atof(argv[4]);

        if (data_count < 0 || bin_count <= 0) {
            fprintf(stderr, "Invalid data_count or bin_count\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        if (argc != 5 + data_count) {
            fprintf(stderr, "Expected %d data values but got %d arguments\n", data_count, argc - 5);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        /* allocate and parse data values */
        data = malloc(sizeof(float) * data_count);
        if (!data) {
            fprintf(stderr, "rank 0: malloc failed\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        for (int i = 0; i < data_count; ++i) {
            data[i] = atof(argv[5 + i]);
        }
    }

    /* Broadcast the basic parameters to all ranks */
    MPI_Bcast(&data_count, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&bin_count, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&min_meas, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&max_meas, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    /* Compute sendcounts/displacements for Scatterv so any data_count is supported */
    int *sendcounts = malloc(sizeof(int) * size);
    int *displs = malloc(sizeof(int) * size);
    if (!sendcounts || !displs) {
        fprintf(stderr, "rank %d: allocation failed for sendcounts/displs\n", rank);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int base = data_count / size;
    int rem = data_count % size;
    for (int i = 0; i < size; ++i) {
        sendcounts[i] = base + (i < rem ? 1 : 0);
    }
    displs[0] = 0;
    for (int i = 1; i < size; ++i) displs[i] = displs[i-1] + sendcounts[i-1];

    int local_count = sendcounts[rank]; /* how many elements this rank will receive */

    /* allocate local buffer (may be zero) */
    float *local_data = NULL;
    if (local_count > 0) {
        local_data = malloc(sizeof(float) * local_count);
        if (!local_data) {
            fprintf(stderr, "rank %d: malloc local_data failed\n", rank);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    /* Scatter variable-sized chunks from root to all ranks */
    MPI_Scatterv(data, sendcounts, displs, MPI_FLOAT,
                 local_data, local_count, MPI_FLOAT,
                 0, MPI_COMM_WORLD);

    /* allocate histogram arrays */
    int *local_bin_counts = calloc(bin_count, sizeof(int)); /* zero-initialized */
    int *total_bin_counts = calloc(bin_count, sizeof(int)); /* only meaningful on rank 0 */
    float *bin_maxes = malloc(sizeof(float) * bin_count);
    if (!local_bin_counts || !total_bin_counts || !bin_maxes) {
        fprintf(stderr, "rank %d: allocation failed for histogram arrays\n", rank);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    /* compute bin width; protect against zero division */
    float bin_width = (bin_count > 0) ? ((max_meas - min_meas) / (float)bin_count) : 0.0f;

    for (int i = 0; i < bin_count; ++i) {
        bin_maxes[i] = min_meas + (i + 1) * bin_width; /* upper edge */
    }

    /* Fill local histogram */
    for (int i = 0; i < local_count; ++i) {
        int bin_index;
        if (bin_width == 0.0f) {
            bin_index = 0; /* all values fall into single bin if range is zero */
        } else {
            bin_index = (int)((local_data[i] - min_meas) / bin_width);
        }
        if (bin_index < 0) bin_index = 0;
        if (bin_index >= bin_count) bin_index = bin_count - 1;
        local_bin_counts[bin_index]++;
    }

    /* reduce local histograms into total on rank 0 */
    MPI_Reduce(local_bin_counts, total_bin_counts, bin_count, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    /* rank 0 prints the histogram */
    if (rank == 0) {
        printf("Histogram (data_count=%d, bins=%d, min=%.2f, max=%.2f)\n", data_count, bin_count, min_meas, max_meas);
        for (int i = 0; i < bin_count; ++i) {
            printf("bin %2d: count=%d  max=%.2f\n", i, total_bin_counts[i], bin_maxes[i]);
        }
    }

    /* cleanup */
    free(sendcounts);
    free(displs);
    if (local_data) free(local_data);
    free(local_bin_counts);
    free(total_bin_counts);
    free(bin_maxes);
    if (rank == 0 && data) free(data);

    MPI_Finalize();
    return 0;
}