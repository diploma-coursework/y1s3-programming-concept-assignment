#pragma once
#ifndef ticket_struct
#define ticket_struct

#include "GeneralStructs.h"

// Functions
scheduleTrainMenu();
paginateTrainScheduleRecordsMenu();
removeTrainScheduleRecordMenu();
chooseTrainScheduleSeatMenu();
getTrainScheduleById();


typedef struct {
    char origin[30];
    char dest[30];
    int pax;
    struct Date date;
} Information;





#endif