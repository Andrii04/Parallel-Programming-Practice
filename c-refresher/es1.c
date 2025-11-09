#include <stdio.h>

void compareNums(int num1, int num2) {
        if (num1>num2) {
            printf("%d greater than %d\n", num1, num2);
        }
        else if (num1 < num2) {
            printf("%d greater than %d\n", num2, num2);
        }
        else if (num1 == num2) {
            printf("%d equal to %d\n", num1, num2);
        }

        int sum = num1+num2;
        int prod = num1*num2;
        printf("Sum: %d\nProd: %d", sum, prod);
    }

    
int main() {
    compareNums(5, 4);
}
