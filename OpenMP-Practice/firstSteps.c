#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv) {
    #pragma omp parallel num_threads(3)
    {
        printf("Helllo from thread num %d\n", omp_get_thread_num());
    }
    return 0;
}