/*********************************************************************/
/*                         PREPROCESSORS                             */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*********************************************************************/
/*                            COLOURS                                */
/*********************************************************************/

#define white "\033[0m"
#define red "\033[1;31m"
#define green "\033[1;32m"
#define blue "\033[1;34m"
#define yellow "\033[1;33m"
#define cyan "\033[1;36m"
#define pink "\033[1;35m"

/*********************************************************************/
/*                         GLOBAL STRUCTURE                          */
/*********************************************************************/

typedef struct {
    char name[30];
    int num_of_seats;
    int train;
    float charges;

} Information;

/*********************************************************************/
/*                       FUNCTIONS DECLARATION                       */
/*********************************************************************/

int viewDetails();							     // View All Train Schedules
int bookTicket();                                // Make Booking
int modifyTicket();                              // Edit Booking Details
int specifictrain(int);						     // Train Selection
float charge(int, int);							 // Payment Calculation
int displayTicket(char name[], int, int, float); // Display Ticket 
int bookHistory();                               // Shows Booking History
int deleteTicket();                              // Cancel Booking


/*********************************************************************/
/*                         TICKET MAIN MENU                          */
/*********************************************************************/

int ticket()
{
    system("cls");

    printf(yellow);
    printf("\n=============================================================\n");
    printf("||          "pink" WELCOME TO THE TICKET BOOKING SYSTEM          "yellow"|| \n");
    printf("||                                                         ||\n");
    printf("||          "blue"         POWERED BY SHURIYA                    "yellow"|| \n");
    printf("=============================================================\n\n");

    printf(green);
    printf("-------------------------------------------------------------\n");
    printf("|                                                           |\n");
    printf("|             "cyan" 1. Book Ticket                              "green" | \n");
    printf("|             "cyan" 2. View Booking History                     "green" | \n");
    printf("|             "cyan" 3. Cancel Booking                           "green" | \n");
    printf("|             "cyan" 4. Exit Program                             "green" | \n");
    printf("|                                                           |\n");
    printf("-------------------------------------------------------------\n");
    printf("\n");

    // Loop For Input 

    int option, valid = 0;
    do {
        printf(yellow"Enter your option (1,2,3,4) > ");
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
            deleteTicket();
            valid = 1;
            break;

        case 4:
            return 0;

        default:
            printf(red"Invalid input. Please re-enter again.\n");
            printf("\n");
            break;
        }
    } while (!valid);
}


/*********************************************************************/
/*                     VIEW TRAIN SCHEDULES MENU                     */
/*********************************************************************/

int viewDetails()
{
    system("cls");
    printf(yellow);
    printf("-----------------------------------------------------------------------------");
    printf("\nTr.No\tName\t\t\tDestinations\t\tCharges\t\tTime\n");
    printf("-----------------------------------------------------------------------------");
    printf(cyan);
    printf("\n1001\tJR East Railway\t\tTokaido Line\t\t1600 Yen\t9am");
    printf("\n1002\tJR East Railway\t\tHachiko Line\t\t1800 Yen\t11am");
    printf("\n1003\tJR East Railway\t\tSagami Line\t\t1400 Yen\t4pm");
    printf("\n1004\tJR East Railway\t\tTsurumi Line\t\t1700 Yen\t1pm");
    printf("\n1005\tJR East Railway\t\tYamanote Line\t\t1900 Yen\t8am");
    printf("\n1006\tJR East Railway\t\tTakasaki Line\t\t1600 Yen\t12pm");
    printf("\n1007\tJR East Railway\t\tKeiyo Line\t\t1500 Yen\t3pm");
    printf("\n1008\tJR East Railway\t\tTokyo Monorail\t\t2000 Yen\t10am");
    printf("\n1009\tJR East Railway\t\tNikko Line\t\t1900 Yen\t9am");
    printf("\n1009\tJR East Railway\t\tRyomo Line\t\t1700 Yen\t2pm");
    printf("\n");
    printf(white);

}


/*********************************************************************/
/*                           BOOKING MENU                            */
/*********************************************************************/

int bookTicket()
{
    Information info;

    FILE* fp;
    fp = fopen("BookingsInfo.bin", "ab");

    viewDetails();

    char confirm;
    int train_num_valid = 0;
    float charges = 0;

    while (!train_num_valid) {
        printf(yellow"\nEnter train number > "white);
        scanf("%d", &info.train);

        // Check if train number is valid
        if (info.train >= 1001 && info.train <= 1010) {
            train_num_valid = 1;

            // Prompt user to enter the name
            printf(yellow"\nEnter Your Name: ");
            printf(white);
            scanf("%s", info.name);

            // Prompt user to enter the number of seats
            printf(yellow"\nEnter Number Of Seats: ");
            printf(white);
            scanf("%d", &info.num_of_seats);

            // Calculate charges
            charges = charge(info.train, info.num_of_seats);

            // Display ticket information
            displayTicket(info.name, info.num_of_seats, info.train, charges);
        }
        else {
            printf(red"\nInvalid train Number! Please re-enter again.\n"yellow);
        }

        // Clear input buffer
        while (getchar() != '\n');
    }

    while (1) {
        printf(yellow"\nEnter Choice (y/n) > "white);
        scanf(" %c", &confirm);

        // Clear input buffer
        while (getchar() != '\n');

        if (confirm == 'y' || confirm == 'Y') {
            // Ticket confirmed
            fprintf(fp, "%s\t\t%d\t\t%d\t\t%.2f\n", info.name, info.num_of_seats, info.train, charges);
            printf("\n");
            printf(green"       ===================\n");
            printf(cyan"          Ticket Booked!\n");
            printf(green"       ===================\n"white);
            break;
        }
        else if (confirm == 'n' || confirm == 'N') {
            // Ticket not confirmed
            printf("\n");
            printf(green"       ===================\n");
            printf(cyan"        Booking Cancelled!\n");
            printf(green"       ===================\n"white);
            break;
        }
        else {
            // Invalid input
            printf(red"\nInvalid choice entered! Please re-enter again.\n"yellow);
        }
    }
    fclose(fp);

    // Loop For Input 

    printf("\n");
    printf(blue"1. Edit Booking\n");
    printf(blue"2. Return Main Menu\n");

    int option, valid = 0;
    do {
        printf(yellow"\nEnter Your Option (1,2) > ");
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
            modifyTicket();
            valid = 1;
            break;

        case 2:
            return ticket();

        default:
            printf(red"Invalid input. Please re-enter again.\n");
            printf("\n");
            break;
        }
    } while (!valid);

}


/*********************************************************************/
/*                        MODIFY BOOKING MENU                        */
/*********************************************************************/

int modifyTicket() {
    system("cls");
    printf(yellow"=======================\n");
    printf(cyan"   Modify Booking\n");
    printf(yellow"=======================\n\n");

    char name[30];
    int train_num;
    int new_num_of_seats;

    // Prompt user for ticket details to be modified
    printf(yellow"Enter name: ");
    printf(white);
    scanf("%s", name);

    printf(yellow"Enter train number: ");
    printf(white);
    scanf("%d", &train_num);

    printf(yellow"Enter new number of seats: ");
    printf(white);
    scanf("%d", &new_num_of_seats);

    // Open the binary file for reading and a temporary file for writing
    FILE* fp = fopen("BookingsInfo.bin", "rb");
    FILE* temp_fp = fopen("temp.bin", "wb");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Read each record from the binary file

    Information read_info;
    int found = 0;
    while (fread(&read_info, sizeof(Information), 1, fp) == 1)
    {
        // If the record matches the ticket to be modified, update it with the new details
        if (strcmp(read_info.name, name) == 0 && read_info.train == train_num)
        {
            found = 1;
            // Update the number of seats
            read_info.num_of_seats = new_num_of_seats;
            printf(yellow"\nBooking found and modified.\n");
        }

        // Write the record to the temporary file
        fwrite(&read_info, sizeof(Information), 1, temp_fp);
    }

    fclose(fp);
    fclose(temp_fp);

    // Delete the original file
    remove("BookingsInfo.bin");
    // Rename the temporary file to the original filename
    rename("temp.bin", "BookingsInfo.bin");

    if (!found)
    {
        printf(red"\nBooking not found!\n");
    }

    return 0;
}


/*********************************************************************/
/*                       TRAIN SELECTION MENU                        */
/*********************************************************************/

int specifictrain(int train_num)
{

    if (train_num == 1001)
    {
        printf(yellow"  -----------------------------"cyan);
        printf("\n   Train      : JR East Railway\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Destination: Tokaido Line\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Departure  : 9am\n");
        printf(yellow"  -----------------------------\n"cyan);

    }
    if (train_num == 1002)
    {
        printf(yellow"  -----------------------------"cyan);
        printf("\n   Train      : JR East Railway\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Destination: Hachiko Line\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Departure  : 11am\n");
        printf(yellow"  -----------------------------\n"cyan);

    }
    if (train_num == 1003)
    {

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Train      : JR East Railway\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Destination: Sagami Line\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Departure  : 4pm\n");
        printf(yellow"  -----------------------------\n"cyan);

    }
    if (train_num == 1004)
    {
        printf(yellow"  -----------------------------"cyan);
        printf("\n   Train      : JR East Railway\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Destination: Tsurumi Line\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Departure  : 1pm\n");
        printf(yellow"  -----------------------------\n"cyan);

    }
    if (train_num == 1005)
    {
        printf(yellow"  -----------------------------"cyan);
        printf("\n   Train      : JR East Railway\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Destination: Yamanote Line\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Departure  : 8am\n");
        printf(yellow"  -----------------------------\n"cyan);

    }
    if (train_num == 1006)
    {
        printf(yellow"  -----------------------------"cyan);
        printf("\n   Train      : JR East Railway\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Destination: Takasaki Line\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Departure  : 12pm\n");
        printf(yellow"  -----------------------------\n"cyan);

    }
    if (train_num == 1007)
    {
        printf(yellow"  -----------------------------"cyan);
        printf("\n   Train      : JR East Railway\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Destination: Keiyo Line\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Departure  : 3pm\n");
        printf(yellow"  -----------------------------\n"cyan);

    }
    if (train_num == 1008)
    {
        printf(yellow"  -----------------------------"cyan);
        printf("\n   Train      : JR East Railway\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Destination: Tokyo Monorail\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Departure  : 10am\n");
        printf(yellow"  -----------------------------\n"cyan);

    }
    if (train_num == 1009)
    {
        printf(yellow"  -----------------------------"cyan);
        printf("\n   Train      : JR East Railway\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Destination: Nikko Line\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Departure  : 9am\n");
        printf(yellow"  -----------------------------\n"cyan);

    }
    if (train_num == 1010)
    {
        printf(yellow"  -----------------------------"cyan);
        printf("\n   Train      : JR East Railway\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Destination: Ryomo Line\n");
        printf(yellow"  -----------------------------\n"cyan);

        printf(yellow"  -----------------------------"cyan);
        printf("\n   Departure  : 2pm\n");
        printf(yellow"  -----------------------------\n"cyan);

    }
}


/*********************************************************************/
/*                           PAYMENT MENU                            */
/*********************************************************************/

float charge(int train_num, int num_of_seats)
{
    if (train_num == 1001)
    {
        return(1600.0 * num_of_seats);
    }
    if (train_num == 1002)
    {
        return(1800.0 * num_of_seats);
    }
    if (train_num == 1003)
    {
        return(1400.0 * num_of_seats);
    }
    if (train_num == 1004)
    {
        return(1700.0 * num_of_seats);
    }
    if (train_num == 1005)
    {
        return(1900.0 * num_of_seats);
    }
    if (train_num == 1006)
    {
        return(1600.0 * num_of_seats);
    }
    if (train_num == 1007)
    {
        return(1500.0 * num_of_seats);
    }
    if (train_num == 1008)
    {
        return(2000.0 * num_of_seats);
    }
    if (train_num == 1009)
    {
        return(1900.0 * num_of_seats);
    }
    if (train_num == 1010)
    {
        return(1700.0 * num_of_seats);
    }
}


/*********************************************************************/
/*                        DISPLAY TICKET MENU                        */
/*********************************************************************/

int displayTicket(char name[], int num_of_seats, int train_num, float charges) {

    system("cls");

    FILE* fp = fopen("BookingsInfo.bin", "rb");

    Information read_info;

    printf("\n");
    printf(yellow"=======Booking Information=======\n\n"cyan);

    printf(yellow"  -----------------------------"cyan);
    printf("\n   Name       : %s\n", name);
    printf(yellow"  -----------------------------\n"cyan);

    printf(yellow"  -----------------------------"cyan);
    printf("\n   Seats      : %d\n", num_of_seats);
    printf(yellow"  -----------------------------\n"cyan);

    printf(yellow"  -----------------------------"cyan);
    printf("\n   Train No.  : %d\n", train_num);
    printf(yellow"  -----------------------------\n"cyan);

    specifictrain(train_num);

    printf(yellow"  -----------------------------"cyan);
    printf("\n   Charges    : %.2f Yen\n", charges);
    printf(yellow"  -----------------------------\n"cyan);

    printf("\n");

    fclose(fp);
}


/*********************************************************************/
/*                        BOOKING HISTORY MENU                       */
/*********************************************************************/

int bookHistory() {
    system("cls");

    FILE* fp = fopen("BookingsInfo.bin", "rb");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf(yellow"               ==============================\n");
    printf(cyan"                      Booking History\n");
    printf(yellow"               ==============================\n\n");

    printf(cyan"   Name\t\t  Seats\t\t Train No.\tCharges\n");
    printf(pink"  -------------------------------------------------------------\n"green);

    // Read and display all tickets
    Information read_info;
    while (fread(&read_info, sizeof(Information), 1, fp) == 1) {
        // Display each booking
        printf("  %-30s%-10d%-12d%.2f\n", read_info.name, read_info.num_of_seats, read_info.train, read_info.charges);
    }

    fclose(fp);

    // Loop For Input 
    int option;
    do {
        printf(yellow"\nPress 1 to Return To Main Menu > ");
        printf(white);
        if (scanf("%d", &option) != 1) {    // Check for valid input
            printf(red"Invalid input. Please enter a number.\n");
            printf("\n");
            while (getchar() != '\n');      // Clear input buffer
            continue;                      // Restart the loop
        }

        switch (option) {
        case 1:
            return ticket();
        default:
            printf(red"Invalid input. Please re-enter again.\n");
            printf("\n");
            break;
        }
    } while (1); // Loop indefinitely until a valid input is received

    return 0;
}


/*********************************************************************/
/*                         DELETE BOOKING MENU                       */
/*********************************************************************/

int deleteTicket() {
    system("cls");
    printf(yellow"=======================\n");
    printf(cyan"   Cancel Booking\n");
    printf(yellow"=======================\n\n");

    char name[30];
    int train_num;

    // Prompt user for ticket details to be deleted
    printf(yellow"Enter name: ");
    printf(white);
    scanf("%s", name);

    printf(yellow"Enter train number: ");
    printf(white);
    scanf("%d", &train_num);

    // Open the binary file for reading and a temporary file for writing
    FILE* fp = fopen("BookingsInfo.bin", "rb");
    FILE* temp_fp = fopen("temp.bin", "wb");

    if (fp == NULL || temp_fp == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    // Read each record from the binary file
    Information read_info;
    int found = 0;
    while (fread(&read_info, sizeof(Information), 1, fp) == 1) {
        // If the record matches the ticket to be deleted, skip it
        if (strcmp(read_info.name, name) == 0 && read_info.train == train_num) {
            found = 1;
            printf(yellow"\nBooking found and cancelled.\n");
            continue;
        }

        // Otherwise, write it to the temporary file
        fwrite(&read_info, sizeof(Information), 1, temp_fp);
    }

    fclose(fp);
    fclose(temp_fp);

    // Delete the original file

    remove("BookingsInfo.bin");

    // Rename the temporary file to the original filename
    rename("temp.bin", "BookingsInfo.bin");

    if (!found) {
        printf(red"\nBooking not found!\n");
    }
    return 0;
}