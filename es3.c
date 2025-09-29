#include <stdio.h>

void numRange(int num) {
    for (int i = num; i >= 0; i--) {
        printf("%d\n", i);
    }
}

int main() {
    numRange(10);
}