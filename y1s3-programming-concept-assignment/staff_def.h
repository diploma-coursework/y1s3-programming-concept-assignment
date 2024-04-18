#pragma once
#include "SystemEnums.h"
#include "GeneralStructs.h"

#ifndef staff_def
#define staff_def

struct staff {
	char id[10];
	char name[30];
	char pass[40];
};

struct menu {
	int choice;
	int valid;
};

struct info {
    enum Position position;
    int salary;
    int age;
};

// ANSI colour values defination
#define blue "\033[1;34m"
#define green "\033[1;32m"
#define yellow "\033[1;33m"
#define red "\033[1;31m"
#define reset "\033[0m"
#define bold "\033[1;0m"


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

// Function to get the current time
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


#endif