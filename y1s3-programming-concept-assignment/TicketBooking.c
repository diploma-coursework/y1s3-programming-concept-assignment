#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ticket_struct.h"


// Member main 
void mainTicket() {
    char name[20];
    char pass[20];
    printf("\033[1;33m"); // Set text color to yellow
    printf("\n=================================================================\n");
    printf("||             \033[1;35mWELCOME TO THE TICKET BOOKING SYSTEM\033[1;33m            ||\n");
    printf("||                                                             ||\n");
    printf("||                     \033[1;36mPOWERED BY SHURIYA\033[1;33m                      ||\n");
    printf("=================================================================\n\n");
    printf("\033[0m"); // Reset text color to default

    printf("\033[1;32m"); // Set text color to green
    printf("-------------------------------------------------------------\n");
    printf("|                                                           |\n");
    printf("|             \033[1;34m1. Option 1\033[1;32m                                   |\n");
    printf("|             \033[1;34m2. Option 2\033[1;32m                                   |\n");
    printf("|             \033[1;34m3. Option 3\033[1;32m                                   |\n");
    printf("|             \033[1;34m4. Exit\033[1;32m                                       |\n");
    printf("|                                                           |\n");
    printf("-------------------------------------------------------------\n");
    printf("\033[0m"); // Reset text color to default
};

