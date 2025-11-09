#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void es1_2() {
    int *array;
    int newNum;
    int sizeArray = 0;

    while (true) {
        printf("Insert Next Number\n");
        scanf("%d", &newNum);
        if (newNum == 0) {
            break;
        }
        array = realloc(array, sizeof(int) * (++sizeArray));
        array[sizeArray-1] = newNum;
    }
    int sum = 0;
    for (int i=0; i<sizeArray; i++) {
        sum += array[i];
    }
    printf("%d", sum);
    free(array);

}


int main() {
    es1_2();
}

