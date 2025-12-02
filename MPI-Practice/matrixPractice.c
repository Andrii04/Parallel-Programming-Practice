#include <stdio.h>
#include <stdlib.h>

void printMatrix() {
    int M[4][4];

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            M[i][j] = i;
        }
    }

    for (int i=0; i<4; i++) {
        printf("[");
        for (int j=0; j<4; j++) {
            printf(" %d", M[i][j]);
        }
        printf(" ]\n");
    }
}