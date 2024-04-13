#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ticket_struct.h"

// Colours
#define white "\033[0m"
#define red "\033[1;31m"
#define green "\033[1;32m"
#define blue "\033[1;34m"
#define yellow "\033[1;33m"
#define cyan "\033[1;36m"
#define pink "\033[1;35m"   

int Ticket() {
    
    // Main Screen Banner
    printf(yellow);
    printf("\n=============================================================\n");
    printf("||          "pink" WELCOME TO THE TICKET BOOKING SYSTEM          "yellow"|| \n");
    printf("||                                                         ||\n");
    printf("||          "cyan"         POWERED BY SHURIYA                    "yellow"|| \n");
    printf("=============================================================\n\n");

    printf(green); 
    printf("-------------------------------------------------------------\n");
    printf("|                                                           |\n");
    printf("|             "blue" 1. Book Ticket                              "green" | \n");
    printf("|             "blue" 2. View Booking                             "green" | \n");
    printf("|             "blue" 3. Cancel Booking                           "green" | \n");
    printf("|             "blue" 4. Exit                                     "green" | \n");
    printf("|                                                           |\n");
    printf("-------------------------------------------------------------\n");
    printf("\n");

    // Variables
    int option, valid = 0;              

    do {
        printf(cyan"Enter your option (1,2,3,4) > ");
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
            bookTicket();
            valid = 1;
            break;

        case 2:                // Exit Program
            displayTicket();
            valid = 1;
            break;

        case 3:
            deleteTicket();
            valid = 1;
            break;
        
        case 4:
            return 0;

        default:              // Other Values
            printf(red"Invalid input. Please re-enter again.\n");
            printf("\n");
            break;
        }
    } while (!valid);
};

// Functions 

int bookTicket() {
    system("cls");
    
    // add
    // modify/edit
    // display seat
    // payment
};

int addTicket() {               // Booking
    system("cls");
    printf("This is the add ticket page");
};

int modifyTicket() {             // Booking
    system("cls");
    printf("This is the modify ticket page");
};

int displaySeats() {             // Booking
    system("cls");
    printf("This is the display seats page");
};

int paymentProcessing() {        // Booking
    system("cls");
    printf("This is the payment ticket page");
};





int displayTicket() {            // View Booking
    system("cls");
    printf("This is the display ticket page");
};





int deleteTicket() {             // Cancel Booking
    system("cls");
    printf("This is the delete ticket page");
};



int searchTicket() {            // IDK
    system("cls");
    printf("This is the search ticket page");
};

