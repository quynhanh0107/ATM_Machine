#include <stdio.h>
#include "atm.h"
#include "utils.h"

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
        if (scanf("%d", &choice) != 1) {
            printf("You did not enter an integer! Try again!\n\n");
            clearBuffer();
            continue;
        }

        switch (choice) {
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

void withdrawal(double* balance) {
    int withdraw_money;
    int notes50, notes20;
    while (1) {
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
                printf("\n**********\nCancelled.\n*******\n");
                printf("\n***** Balance: %.2lf\n\n", *balance);
                break;
            }
            if (withdraw_money > *balance - 20) {
                printf("Cannot withdraw more than available balance leaving at least 20 euros! Try again.\n");
                continue;
            }
            if (
                withdraw_money < 20 ||
                withdraw_money > 1000 ||
                withdraw_money % 10 != 0 ||
                (withdraw_money % 20 != 0 && withdraw_money % 50 != 0 && withdraw_money < 50)
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
                    int remainder = withdraw_money - 50 * i;
                    if (remainder % 20 == 0) {
                        notes20 = remainder / 20;
                        notes50 = i;
                        break;
                    }
                }
            }
            int return_draw = notes20 * 20 + notes50 * 50;
            *balance -= return_draw;
            printf("\n**************\nWithdrawal ok.\n*************\n");
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
    while (1) {
        printf("\nGive the money to deposit (min. 10.00, max. 1000.00 max. (max. saldo 2000.00)): ");

        if (scanf("%lf", &deposit_money) != 1) {
            printf("Not an integer! Try again.\n");
            clearBuffer();
            continue;
        }
        if (deposit_money == 0) {
            printf("\n**********\nCancelled.\n*******\n");
            printf("\n***** Balance: %.2lf\n\n", *balance);
            break;
        }
        if (deposit_money < 10 || deposit_money > 1000) {
            printf("Not a valid number! Try again.\n");
            continue;
        }

        *balance += deposit_money;
        if (*balance > 2000) {
            printf("The deposit amount exceeds the max saldo! Try again.\n");
            continue;
        } else {
            printf("\n***********\nDeposit ok.\n***********\n");
            printf("\n***** Balance: %.2lf\n\n", *balance);
            break;
        }
    }
}
