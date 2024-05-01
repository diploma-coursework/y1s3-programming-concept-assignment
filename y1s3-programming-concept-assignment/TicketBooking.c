#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Header Files
#include "BookingStruct.h"
#include "GeneralStructs.h"
#include "GeneralUtils.h"
#include "SystemEnums.h"
#include "TrainSchedulingModule.h"
#include "TrainSchedulingModuleUtils.h"

// Colours
#define white "\033[0m"
#define red "\033[1;31m"
#define green "\033[1;32m"
#define blue "\033[1;34m"
#define yellow "\033[1;33m"
#define cyan "\033[1;36m"
#define pink "\033[1;35m"   

// Functions
//scheduleTrainMenu();
//paginateTrainScheduleRecordsMenu();
//removeTrainScheduleRecordMenu();
//chooseTrainScheduleSeatMenu();
//getTrainScheduleById(id here);


// Ticket Main Menu 
int ticket() {
    system("cls");

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
    printf("|             "blue" 2. View All Bookings                        "green" | \n");
    printf("|             "blue" 3. Exit Program                             "green" | \n");
    printf("|                                                           |\n");
    printf("-------------------------------------------------------------\n");
    printf("\n");

    // Variables
    int option, valid = 0;

    // Loop For Input 
    do {
        printf(cyan"Enter your option (1,2,3) > ");
        printf(white);
        if (scanf("%d", &option) != 1)     // Char is entered
        {
            printf(red"Invalid input. Please enter a number.\n");
            printf("\n");
            while (getchar() != '\n');    // Clear input buffer
            continue;                    // Restart the loop
        }

        switch (option) {

        case 1:
            bookTicket();
            valid = 1;
            break;

        case 2:
            bookHistory();
            valid = 1;
            break;

        case 3:
            return 0;

        default:
            printf(red"Invalid input. Please re-enter again.\n");
            printf("\n");
            break;
        }
    } while (!valid);
}

// Book Ticket Menu
int bookTicket() {

    system("cls");
    printf(yellow"-------------------------------"cyan);
    printf("\nState Booking Information Below\n");
    printf(yellow"-------------------------------\n\n"cyan);

    // Prompt User to Enter Information
    Information info;

    printf("Enter Origin: ", info.origin);
    scanf("%s", info.origin);
    printf("Enter Destination: ", info.dest);
    scanf("%s", info.dest);
    printf("Enter number of passengers: ", info.pax);
    scanf("%d", &info.pax);
    printf("Enter Date (DD/MM/YYYY): ", info.date.day, info.date.month, info.date.year);
    scanf("%d/%d/%d", &info.date.day, &info.date.month, &info.date.year);
    printf("\n");
    printf(yellow"----------------------------\n"yellow);

    // Create Binary File To Store Information 

    //  Write Info
    FILE* fp = fopen("BookingsInfo.bin", "wb");

    if (fp == NULL) {
        printf("Error Saving Data!");
        return 1;
    }

    fwrite(&info, sizeof(Information), 1, fp);

    fclose(fp);


    printf("\nYour Information Has Been Recorded!\n\n");

    printf(green"1. Select Depart Ticket\n");
    printf(green"2. Edit Booking Details\n");
    printf(green"3. Back to Main Menu\n");
    printf("\n\n");

    // Variables
    int option, valid = 0;

    // Loop For Input 
    do {
        printf(cyan"Enter your option (1,2,3) > ");
        printf(white);
        if (scanf("%d", &option) != 1)     // Char is entered
        {
            printf(red"Invalid input. Please enter a number.\n");
            printf("\n");
            while (getchar() != '\n');    // Clear input buffer
            continue;                    // Restart the loop
        }

        switch (option) {

        case 1:
            displayTicket();
            valid = 1;
            break;

        case 2:
            modifyTicket();
            valid = 1;
            break;

        case 3:
            system("cls");
            return ticket();
            break;

        default:
            printf(red"Invalid input. Please re-enter again.\n");
            printf("\n");
            break;
        }
    } while (!valid);
}

// Edit Menu - Edit The Values in Book Ticket
int modifyTicket() {
    system("cls");
    printf(yellow"----------------------------"cyan);
    printf("\nEdit Your Ticket Below\n");
    printf(yellow"----------------------------\n\n"cyan);
}

// Select Depart Ticket And Check Available Seats
int displaySeats() {
    system("cls");
    printf("This is the display seats page");

    /*
    - shows from where to where
    - the date
    - express -26 (name)
    - available seats
    - arriving time
    - journey how many hours
    - price

    Select Seat Number
    */
}

// Display Menu - View Booking Info
int displayTicket() {
    system("cls");

    /*
    - Show Booking Details and Payment
    (Coach T2, time , selected ticket type and ticket number, seat no)
    */


    // Read and Display Information From The Binary File 

    // Read Info
    FILE* fp = fopen("BookingsInfo.bin", "rb");

    Information read_info;

    fread(&read_info, sizeof(Information), 1, fp);

    fclose(fp);


    // Display Info
    printf(yellow"=======Booking Information=======\n\n"cyan);

    printf(yellow"----------------------------"cyan);
    printf("\nOrigin      : %s\n", read_info.origin);
    printf(yellow"----------------------------\n"cyan);

    printf(yellow"----------------------------"cyan);
    printf("\nDestination : %s\n", read_info.dest);
    printf(yellow"----------------------------\n"cyan);

    printf(yellow"----------------------------"cyan);
    printf("\nPax No      : %d\n", read_info.pax);
    printf(yellow"----------------------------\n"cyan);

    printf(yellow"----------------------------"cyan);
    printf("\nDate        : %d/%d/%d\n", read_info.date.day, read_info.date.month, read_info.date.year);
    printf(yellow"----------------------------\n"cyan);


    // paymentProcessing();       // Proceeds to here for payment
}

int paymentProcessing() {      // Payment Menu
    system("cls");
    printf("This is the payment ticket page");

    // Booking will be confirmed upon payment being completed
}


// History Menu

int bookHistory() {
    system("cls");
    printf("This is the Booking History!");

    searchTicket();  // Search Ticket
    deleteTicket();  // Cancel Ticket
}

// Delete Menu

int deleteTicket() {             // Cancel Booking
    system("cls");
    printf("This is the delete ticket page");
}

// Search Menu

int searchTicket() {            // Its like search for ticket using TicketID 
    system("cls");
    printf("This is the search ticket page");
}

// Until Here History Menu