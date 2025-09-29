#include <stdio.h>

void numRange(int num) {
    int i = 0;
    while (i <= num) {
        printf("%d\n", i);
        i++;
    }
}

int main() {
    numRange(10);
}