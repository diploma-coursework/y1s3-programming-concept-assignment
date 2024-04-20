#pragma once
#include "SystemEnums.h"
#include "GeneralStructs.h"

#ifndef staff_def
#define staff_def

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

// ANSI colour values defination
#define blue "\033[1;34m"
#define green "\033[1;32m"
#define yellow "\033[1;33m"
#define red "\033[1;31m"
#define reset "\033[0m"
#define bold "\033[1;0m"

//the enum position values converting into strings
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


// boolean identifier
bool valid;
bool found;

/*
if the struct functions being called it will return the current time.

*/

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