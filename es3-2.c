#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void es3_2() {

    typedef struct {
        char* prezzo;
        char* cilindrata;
        char* modello;
        char* colore;
    } Automobile;

    char* currentRecord;
    char* newVal;
    Automobile array[3];
    Automobile CAR;

    int currentCar = 1;
    int i = -1;
    while (currentCar < 4) {
        i++;
        switch (i) {
            case 0 : currentRecord = &(CAR.prezzo);
            case 1 : currentRecord = &(CAR.cilindrata);
            case 2 : currentRecord = &(CAR.modello);
            case 3 : {
                currentRecord = &(CAR.colore);
                currentCar++;
                i = -1;
        }
        printf("Select Car %d's %s\n", currentCar, currentRecord);
        scanf("%s", &newVal);
        currentRecord = newVal;
    }
}


int main() {

}