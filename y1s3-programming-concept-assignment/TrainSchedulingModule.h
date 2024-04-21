#pragma once

#include <stdbool.h>

bool scheduleTrainMenu();

void paginateTrainScheduleRecordsMenu();

void removeTrainScheduleRecordMenu();

void chooseTrainScheduleSeatMenu(int scheduleId, int seatAmount, char seatsSelectedInfo[][4]);