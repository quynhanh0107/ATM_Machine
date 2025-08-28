#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "atm.h"
#include "utils.h"

int main(void) {
    char accNumber[256];
    FILE *accFile;
    double saldo;
    int result;
    char pinCode[256];
    char checkPin[256];
    char continueChoice;

    printf("*** Welcome to use the ATM! ***");

    do {
        printf("\n\nGive account number: ");
        fgets(accNumber, 256, stdin);
        if (accNumber[strlen(accNumber) - 1] == '\n')
            accNumber[strlen(accNumber) - 1] = '\0';
        else
            clearBuffer();

        strcat(accNumber, ".acc.txt");

        printf("DEBUG: Trying to open file: '%s'\n", accNumber);
        accFile = fopen(accNumber, "r");

        if (accFile != NULL) {
            int attempt;
            for (attempt = 0; attempt < 3; attempt++) {
                rewind(accFile);

                printf("\nGive your account PIN code (%d - try): ", attempt + 1);

                fgets(pinCode, 256, stdin);
                if (pinCode[strlen(pinCode) - 1] == '\n') {
                    pinCode[strlen(pinCode) - 1] = '\0';
                } else {
                    clearBuffer();
                }

                fgets(checkPin, 256, accFile);
                if (checkPin[strlen(checkPin) - 1] == '\n')
                    checkPin[strlen(checkPin) - 1] = '\0';
                if (checkPin[strlen(checkPin) - 1] == '\r')
                    checkPin[strlen(checkPin) - 1] = '\0';

                if ((result = strcmp(pinCode, checkPin)) == 0) {
                    fscanf(accFile, "%lf", &saldo);
                    showMenu(&saldo);
                    break;
                } else {
                    if (attempt < 2) {
                        printf("***** Wrong PIN code! Try again.\n");
                    }
                }
                if (attempt == 2) {
                    printf("\n\n***** Too many wrong attempts!");
                    printf("\nYour account is closed\n\n.");
                    fclose(accFile);
                    break;
                }
            }
        } else {
            perror("DEBUG: fopen error");
            printf("\n*****Account doesn't exist. Try again!\n");
            continue;
        }

        while (1) {
            printf("\nDo you want to continue with another account(Y/N)? ");
            scanf(" %c", &continueChoice);
            clearBuffer();
            if (continueChoice == 'y' || continueChoice == 'Y') {
                break;
            } else if (continueChoice == 'n' || continueChoice == 'N') {
                return 0;
            } else {
                printf("Not a valid input. Try again!\n");
                continue;
            }
        }
    } while (1);
    return 0;
}
