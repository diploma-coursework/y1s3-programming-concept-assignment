#include "Ticket_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Colours
#define white "\033[0m"
#define red "\033[1;31m"
#define green "\033[1;32m"
#define blue "\033[1;34m"
#define yellow "\033[1;33m"
#define cyan "\033[1;36m"
#define pink "\033[1;35m"   

int bookTicket() {
    
    // Main Screen Banner
    printf(yellow);
    printf("\n=============================================================\n");
    printf("||          "pink" WELCOME TO THE TICKET BOOKING SYSTEM          "yellow"|| \n");
    printf("||                                                         ||\n");
    printf("||          "cyan"         POWERED BY SHURIYA                    "yellow"|| \n");
    printf("=============================================================\n\n");

    printf(" "green" 1. Login        \n");
    printf(" "green" 2. Exit         \n\n");


    //Variables
    int option, valid = 0;              

    do {
        printf(yellow"Enter your option (1,2) > ");
        printf(white);
        if (scanf("%d", &option) != 1)     // Check if scanf fails to read an integer
        { 
            printf(red"Invalid input. Please enter a number.\n");
            printf("\n");
            while (getchar() != '\n');    // Clear input buffer
            continue;                    // Restart the loop
        }

        switch (option) {

        case 1:                 // Proceed to Next Menu
            memberLogin();
            valid = 1;
            break;

        case 2:                // Exit Program
            return 0;

        default:              // Other Values
            printf(red"Invalid input. Please re-enter again.\n");
            printf("\n");
            break;
        }
    } while (!valid);
};

int memberLogin() {

    system("cls");

    // Variables
    char name[20];
    char pass[20];
    char id[10];

    printf("This Is The Login Page!\n");
    printf("Enter Your Member ID: ", id);
    scanf("%c\n", &id);

};
