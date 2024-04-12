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


char name[20];
char pass[20];
int option ,validity = 0;

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


    // Statement For Entering Value From User
    printf(yellow"Enter number (1,2) > "white);
    scanf("%d", &option);


    // Loop For User To Enter Stated Values
    do {
        switch (option) {

        case 1:                 // Proceed to Next Menu
            memberLogin();
            validity = 1;
            break;

        case 2:                // Exit Program
            return 0;

        default:              // Other Values Repeat Loop
            printf(red"You have not entered the stated values" white);
            printf("\n"); 
            break;
        }
    } while (!validity);
};

int memberLogin() {

    system("cls");

    printf("Some random bullshit here i dont know");
};
