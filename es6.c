#include <stdio.h>

void arrayPointerInput() {
    char array[10];
    char inptChar;
    char *p1;
    p1 = &array[0];
    printf("Type a char to insert into the array:\n");
    scanf("%c",&inptChar);

    for (int i = 0; i < 10; i++) {
        array[i] = (char) i;
    }

    for (int k = 0; k < 10; k++) {
        *p1 = inptChar;
        p1++;
    }

    for (int j = 0; j < 10; j++) {
        printf("%c", array[j]);
    }
}

int main() {
    arrayPointerInput();
}