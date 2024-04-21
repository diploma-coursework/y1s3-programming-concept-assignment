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
	double price;
	int seatsBitfield;
};

int getNumberOfScheduleRecordsInFile();

void displayTrainScheduleMetadata(struct TrainScheduleRecord* record);

bool writeTrainScheduleToFile(struct TrainScheduleRecord* record);

void getTrainSchedulesFromFile(struct TrainScheduleRecord* records);

struct TrainScheduleRecord getTrainScheduleById(int scheduleId);

bool removeTrainScheduleFromFile(int scheduleId);

char* seatsBitFieldToBinary(int seatsBitField);

char* seatsBinaryToGraphic(char* seatsBinary);