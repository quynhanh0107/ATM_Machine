/*

***ATM Machine - Homework***

Introduction:
    - The ATM Machine allows users to interact with their bank accounts and perform banking
    operations such as checking their balance, making deposits, and withdrawing cash.
    - This is also a multi-user ATM, which allows to "log in" with 2 accounts (12345 and 123456)
Functionality:
    1. User validation
        - User inputs account number.
            + If it matches the name of the text file, the program proceeds to ask PIN Code.
            + If not, the program will keep ask the user until they give the valid number.
        - User inputs PIN Code.
            + After inputting correctly account number, user is asked to give PIN Code.
            + If it matches the name of the text file, the program proceeds to ask PIN Code.
            + If not, the program will keep ask the user until the max attempt is reached (max. 3 times).
            + After 3 wrong attempt, the account is closed, and the program will ask if user wants to continue
            with another account.
    2. Main menu
        - After successfully validating the user, the program will show the main menu from where the
        user can choose an action for the given account: withdraw or deposit money, ask for the balance
        or end.
        - The user can perform several (different) actions on the given account sequentially
        (until end is selected).
        - Here are the options:
            + (1) Withdrawal: Users can withdraw money in multiples of 20 or 50 euros, subject to maintaining
            a minimum balance of 20 euros. Number 0 is pressed to cancel.
            + (2) Deposit: Users can deposit amounts between 10 and 1000 euros, ensuring the account balance
            does not exceed 2000 euros. Number 0 is pressed to cancel.
            + (3) Balance Inquiry: Users can view their current account balance.
            + (9) Quit: Allows users to exit the menu.
    3. Loading a different account
        - Before exiting, the user is asked if they want to continue with another account.
            + Press Y/y to continue and the process starts again.
            + Press N/n to stop the program.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clearBuffer(void);
void showMenu(double* balance);
void withdrawal(double* balance);
void deposit(double* balance);

int main(void) {

    char accNumber[256];
    FILE *accFile;
    double saldo;
    int result;
    int choice;
    char pinCode[256];
    char checkPin[256];
    char continueChoice;

    printf("*** Welcome to use the ATM! ***");

    do {
        printf("\n\nGive account number: ");

		fgets(accNumber, 256, stdin);
        if (accNumber[ strlen(accNumber)-1] == '\n')
            accNumber[ strlen(accNumber)-1] = '\0';
        else
            clearBuffer();

        strcat(accNumber, ".acc.txt");

        if ((accFile = fopen(accNumber, "r")) != NULL) {
            int attempt = 0;
            for (attempt = 0; attempt < 3; attempt++){
                rewind(accFile);
                printf("\nGive your account PIN code (%d - try): ", attempt + 1);

                fgets(pinCode, 256, stdin);
                if( pinCode[strlen(pinCode)-1] == '\n'){
                    pinCode[strlen(pinCode)-1] = '\0';
                }
                else{
                    clearBuffer();
                }
                fgets(checkPin, 256, accFile);

                if (checkPin[strlen(checkPin)-1] == '\n')
                    checkPin[strlen(checkPin)-1] = '\0';

                if (checkPin[strlen(checkPin)-1] == '\r')
                    checkPin[strlen(checkPin)-1] = '\0';

                if ((result = strcmp(pinCode, checkPin)) == 0) {
                    fscanf(accFile, "%lf", &saldo);
                    showMenu(&saldo);
                    break;
                }
                else {
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

void showMenu(double* balance) {
    int choice;
    int k = 0;
    while (!k) {
        printf("\n\n************************************************\n");
        printf("Select an option...\n");
        printf("1. = Withdrawal\n");
        printf("2. = Deposit\n");
        printf("3. = Query balance\n");
        printf("9. = Quit\n");
        printf("Your choice: ");
        if(scanf("%d", &choice) != 1) {
            printf("You did not enter an integer! Try again!\n\n");
            clearBuffer(); /*Remember to clear buffer or it will create eternal loop*/
            continue;
        };

        switch(choice)
        {
        case 1:
            withdrawal(balance);
            break;
        case 2:
            deposit(balance);
            break;
        case 3:
            printf("\n\n***** Balance: %.2lf\n\n", *balance);
            break;
        case 9:
            k = 1;
            break;
        default:
            printf("Wrong option! Try again!\n\n");
            continue;
        }
    }
}

void withdrawal(double* balance){
    int withdraw_money;
    int notes50, notes20;
    while(1) {
        if (*balance == 20) {
            int exit_input;
            static int wrongAttempt = 0;
            if (wrongAttempt == 0) {
                printf("\nCan't perform withdrawal! Your account only has 20 euros.\nEnter 0 to return to menu: ");
                wrongAttempt++;
            }
            if (scanf("%d", &exit_input) != 1) {
                wrongAttempt++;
                printf("\nEnter 0 to return to menu: ");
                clearBuffer();
                continue;
            }

            if (exit_input == 0) {
                break;
            } else {
                wrongAttempt++;
                printf("\nEnter 0 to return to menu: ");
                continue;
            }
        } else {
            printf("\nGive the amount to withdraw (full tens: 20, 40-1000): ");

            if (scanf("%d", &withdraw_money) != 1) {
                printf("\nNot an integer! Try again.\n");
                clearBuffer();
                continue;
            }
            if (withdraw_money == 0) {
                    printf("\n**********\n");
                    printf("Cancelled.\n");
                    printf("*******\n");
                    printf("\n***** Balance: %.2lf\n\n", *balance);
                    break;
            }
            if (withdraw_money > *balance - 20) {
                    printf("Cannot withdraw more than available balance leaving at least 20 euros! Try again.\n");
                    continue;
            }
            if (
                    withdraw_money < 20
                    || withdraw_money > 1000
                    || withdraw_money % 10 != 0
                    || withdraw_money % 20 != 0 && withdraw_money % 50 != 0 && withdraw_money < 50
                ) {
                    printf("Not a valid number! Try again!\n");
                    continue;
            }

            for (int i = withdraw_money / 50; i >= 0; i--) {
                if (withdraw_money % 50 == 0) {
                    notes50 = i;
                    notes20 = 0;
                    break;
                } else {
                    int remainder = withdraw_money - 50*i;
                    if (remainder % 20 == 0) {
                    notes20 = remainder / 20;
                    notes50 = i;
                    break;
                    }
                }
            }
            int return_draw = notes20 * 20 + notes50 * 50;
            *balance -= return_draw;
            printf("\n**************\n");
            printf("Withdrawal ok.\n");
            printf("*************\n");
            printf("\nAmount: %d", withdraw_money);
            printf("\n*** Notes 50: %d", notes50);
            printf("\n*** Notes 20: %d", notes20);
            printf("\n\n-> Check: (%d * 50) + (%d * 20) = %d", notes50, notes20, withdraw_money);
            printf("\n\n***** Balance: %.2lf\n\n", *balance);
            break;
        }
    }
}

void deposit(double* balance) {

    double deposit_money;
    while (1){
        printf("\nGive the money to deposit (min. 10.00, max. 1000.00 max. (max. saldo 2000.00)): ");

        if (scanf("%lf", &deposit_money) != 1) {
            printf("Not an integer! Try again.\n");
            clearBuffer();
            continue;
        }
        if (deposit_money == 0) {
            printf("\n**********\n");
            printf("Cancelled.\n");
            printf("*******\n");
            printf("\n***** Balance: %.2lf\n\n", *balance);
            break;
        }
        if (deposit_money < 10 || deposit_money > 1000) {
            printf("Not a valid number! Try again.\n");
            continue;
        }

        *balance = *balance + deposit_money;
        if (*balance > 2000) {
            printf("The deposit amount exceeds the max saldo! Try again.\n");
            continue;
        } else {
            printf("\n***********\n");
            printf("Deposit ok.\n");
            printf("***********\n");
            printf("\n***** Balance: %.2lf\n\n", *balance);
            break;
        }
    }
}

void clearBuffer(void)
{
    while( fgetc(stdin) != '\n');
}
