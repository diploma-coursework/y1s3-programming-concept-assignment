#pragma once
#include "SystemEnums.h"
#include "GeneralStructs.h"

#ifndef StaffDef
#define StaffDef

struct staff {
	char id[15];
	char name[30];
	char pass[40];
    enum Position position;
    int salary;
    int age;
    char phone[15];
};

struct menu {
	int choice;
	int valid;
};

#define NO_CHANGE_SALARY -1
#define NO_CHANGE_PHONE ""
#define NO_CHANGE_AGE -1
#define MAX_AGE 80

//Enum to string 
const char* positionString(enum Position position) {
    switch (position) {
    case TICKETING_AGENT: return "Ticketing Agent";
    case CUSTOMER_SERVICE_REPRESENTATIVE: return "Customer Service Representative";
    case TRAIN_CONDUCTOR: return "Train Conductor";
    case TICKET_INSPECTOR: return "Ticket Inspector";
    case STATION_MANAGER: return "Station Manager";
    case OPERATIONS_MANAGER: return "Operations Manager";
    case TECHNICAL_SUPPORT_STAFF: return "Technical Support Staff";
    case ADMINISTRATIVE_STAFF: return "Administrative Staff";
    case CLEANING_STAFF: return "Cleaning Staff";
    case SECURITY_PERSONNEL: return "Security Personnel";
    default: return "Invalid";
    }
}

//strig to enum
enum Position getPositionEnum(const char* positionString) {
    if (strcmp(positionString, "Ticketing Agent") == 0)
        return TICKETING_AGENT;
    else if (strcmp(positionString, "Customer Service Representative") == 0)
        return CUSTOMER_SERVICE_REPRESENTATIVE;
    else if (strcmp(positionString, "Train Conductor") == 0)
        return TRAIN_CONDUCTOR;
    else if (strcmp(positionString, "Ticket Inspector") == 0)
        return TICKET_INSPECTOR;
    else if (strcmp(positionString, "Station Manager") == 0)
        return STATION_MANAGER;
    else if (strcmp(positionString, "Operations Manager") == 0)
        return OPERATIONS_MANAGER;
    else if (strcmp(positionString, "Technical Support Staff") == 0)
        return TECHNICAL_SUPPORT_STAFF;
    else if (strcmp(positionString, "Administrative Staff") == 0)
        return ADMINISTRATIVE_STAFF;
    else if (strcmp(positionString, "Cleaning Staff") == 0)
        return CLEANING_STAFF;
    else if (strcmp(positionString, "Security Personnel") == 0)
        return SECURITY_PERSONNEL;
    else
        return INVALID_POSITION;
}

// display position
void displayposition() {
    printf("TICKETING_AGENT = 0\nCUSTOMER_SERVICE_REPRESENTATIVE = 1\nTRAIN_CONDUCTOR = 2\nTICKET_INSPECTOR = 3\nSTATION_MANAGER = 4\nOPERATIONS_MANAGER = 5\nTECHNICAL_SUPPORT_STAFF = 6\nADMINISTRATIVE_STAFF = 7\nCLEANING_STAFF = 8\nSECURITY_PERSONNEL = 9\n\n>");
}

// boolean identifier
bool valid;
bool found;

/*
if the struct functions being called it will return the current time.

*/

//get the current date
struct Date getCurrentDate() {
    struct Date currentDate;
    time_t currentTime;
    struct tm* localTime;

    // Get the current time
    time(&currentTime);
    localTime = localtime(&currentTime);

    // Extract date components
    currentDate.day = localTime->tm_mday;
    currentDate.month = localTime->tm_mon + 1;  // Months are 0-indexed
    currentDate.year = localTime->tm_year + 1900; // Years since 1900

    return currentDate;
}

//get the current time
struct Time getCurrentTime() {
    struct Time currentTime;
    time_t rawtime;
    struct tm* timeinfo;

    // Get the current time
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Extract time components
    currentTime.hour = timeinfo->tm_hour;
    currentTime.minute = timeinfo->tm_min;

    return currentTime;
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

bool isValidPhoneNumber(const char* number) {
    int i = 0;

    // Check if the number contains only digits
    while (number[i] != '\0') {
        if (!isdigit(number[i])) {
            return false;
        }
        i++;
    }

    // Check if the number has 10 digits
    if (i != 10) {
        return false;
    }

    // Check if the number starts with 011 to 019
    if (number[0] != '0' || (number[1] != '1' && number[1] != '2')) {
        return false;
    }

    return true;
}

#endif