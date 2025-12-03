#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv) {
    #pragma omp parallel for 
    for (int i=0; i<20; i++) {
        printf("Hello from thread %d\n", omp_get_thread_num());
    }
    return 0;
}