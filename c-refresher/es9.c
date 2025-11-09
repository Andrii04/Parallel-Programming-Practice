#include <stdio.h>
#include <stdbool.h>

int included(int A[], int lenA, int B[], int lenB) {
    //All elements of A are included in B ?
    for (int i = 0; i < lenA; i++) {
        int j = 0;
        while (A[i] != B[j] && j < lenB) j++;
        if (j ==  lenB) return false;
    }
    return true;

}

int main() {
    int A[3] = {1, 2, 3};
    int B[5] = {2, 5, 1, 4};
    printf("%s", included(A, 3, B, 5) ? "true" : "false");
}