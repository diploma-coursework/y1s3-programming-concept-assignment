#pragma once

#include "GeneralStructs.h"

struct TrainScheduleRecord {
	int id;
	struct Date departureDate;
	struct Time departureTime;
	struct Date arrivalDate;
	struct Time arrivalTime;
	enum TrainStations departureStation;
	enum TrainStations arrivalStation;
	int seatsBitfield;
};

void displayTrainScheduleMetadata(struct TrainScheduleRecord *record);