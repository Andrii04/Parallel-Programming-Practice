#include <stdio.h>

void digitStringCheck() {
    char str1[20];
    printf("Type a String lower than 20 chars\n");
    scanf("%s", str1);

    //meglio col while e char != '\0' così non iteri inutilmente dopo la fine 
    for (int i = 0; i < 20; i++) {
        if (str1[i] >= '0' && str1[i] <= '9') {
            str1[i] = '*';
        }
    }

    printf("Result String:\n%s\n", str1);
}

int main() {
    digitStringCheck();
}