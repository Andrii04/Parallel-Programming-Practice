#include <stdio.h>
#include <string.h>

void invertArrays() {
    char array1[5];
    char array2[5];
    char *p1;
    char *p2;
    char inptChar;

    for (int i = 0; i < 4; i++) {
        printf("Select %ddx element for array1:\n", i);
        scanf(" %c", &inptChar);
        array1[i] = inptChar;
        printf("Select %ddx element for array2\n", i);
        scanf(" %c", &inptChar);
        array2[i] = inptChar;
    }

    int len = strlen(array1)-1;
    p1 = &array1[0];
    p2 = &array2[len];
    int val1;

    while (*p1 != '\0' && *p2 != '\0') {
        val1 = *p1;
        *p1 = *p2;
        *p2 = val1;
        p1++;
        p2--;
    }

    for (int j = 0; j < 4; j++) {
        printf("array1: %c, array2: %c\n", array1[j], array2[j]);
    }
}

int main() {
    invertArrays();
}