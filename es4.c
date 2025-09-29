#include <stdio.h>

void arrayFive() {
    int array[5];
    int i = 0;

    for (i; i < 5; i++) {
        printf("Enter Number %d", i);
        scanf("%d", &array[i]);
    }

    printf("[");
    for (int j=0; j<5; j++) {
        printf(" ");
        printf("%d", array[j]);
    }
    printf(" ]");
}

int main() {
    arrayFive();
}