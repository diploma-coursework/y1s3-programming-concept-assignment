#pragma once
#include <stdbool.h>

#ifndef Train_schedule_header
#define Train_schedule_header

bool scheduleTrainMenu();

void paginateAllTrainScheduleRecordsMenu();

void removeTrainScheduleRecordMenu();

void chooseTrainScheduleSeatMenu(int scheduleId, int seatAmount, char seatsSelectedInfo[][4]);

#endif 