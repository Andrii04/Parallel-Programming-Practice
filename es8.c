#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int searchVal(char array[], char val) {
    bool found = false;
    int count = 0;

    char *p;
    p = &array[0];

    while (*p != '\0') {
        if (*p == val) {
            found = true;
            count++;
        }
        p++;
    }

    if (!found) return 404;
    else return count;
}

int main() {
    char array[10] = {'1', '2', '3', '3', '4', '5', '6', '7', '9'};
    int result = searchVal(array, '8');
    if (result == 404) {
        printf("Error Code: %d\n", result);
    }
    else {
        printf("Value found! Number of Occurrences: %d\n", result);
    }
}
