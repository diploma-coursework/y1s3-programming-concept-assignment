#pragma once
#include <stdbool.h>

bool scheduleTrainMenu();

void paginateAllTrainScheduleRecordsMenu();

void removeTrainScheduleRecordMenu();

void chooseTrainScheduleSeatMenu(int scheduleId, int seatAmount, char seatsSelectedInfo[][4]);

