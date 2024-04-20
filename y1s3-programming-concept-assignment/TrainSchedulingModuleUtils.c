#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GeneralUtils.h"
#include "TrainSchedulingModuleUtils.h"


int getNumberOfScheduleRecordsInFile() {
	FILE* filePtr = fopen("TrainSchedules.dat", "rb");
	if (filePtr == NULL) {
		fclose(filePtr);
		return 0;
	}

	// calculate number of records existing in TrainSchedules.dat
	fseek(filePtr, 0, SEEK_END);
	int fileSize = ftell(filePtr);
	int numOfRecords = fileSize / sizeof(struct TrainScheduleRecord);
	fclose(filePtr);
	return numOfRecords;
}


void displayTrainScheduleMetadata(struct TrainScheduleRecord *record) {
	printf("ID: %d\n", (*record).id);
	printf("Price: RM%.2f\n", (*record).price);

	printf("\nDeparture\n");
	printf("=========\n");
	printf("Date: %02d/%02d/%d\n", (*record).departureDate.day, (*record).departureDate.month, (*record).departureDate.year);
	printf("Time: %02d:%02d\n", (*record).departureTime.hour, (*record).departureTime.minute);
	printf("Station: %s\n", trainStationToString((*record).departureStation));
	
	printf("\nArrival\n");
	printf("=========\n");
	printf("Date: %02d/%02d/%d\n", (*record).arrivalDate.day, (*record).arrivalDate.month, (*record).arrivalDate.year);
	printf("Time: %02d:%02d\n", (*record).arrivalTime.hour, (*record).arrivalTime.minute);
	printf("Station: %s\n", trainStationToString((*record).arrivalStation));
}


bool writeTrainScheduleToFile(struct TrainScheduleRecord *record) {
	FILE* filePtr = fopen("TrainSchedules.dat", "ab");
	if (filePtr == NULL) {
		return false;
	}
	fwrite(record, sizeof(struct TrainScheduleRecord), 1, filePtr);
	fclose(filePtr);
	return true;
}


// returns number of records found in TrainSchedules.dat
void getTrainSchedulesFromFile(struct TrainScheduleRecord *records) {
	FILE* filePtr = fopen("TrainSchedules.dat", "rb");
	if (filePtr == NULL) {
		printf("Error opening file for reading.\n");
		
	}

	fread(records, sizeof(struct TrainScheduleRecord), getNumberOfScheduleRecordsInFile(), filePtr);
	fclose(filePtr);
}


struct TrainScheduleRecord getTrainScheduleById(int scheduleId) {
	int numOfRecords = getNumberOfScheduleRecordsInFile();
	struct TrainScheduleRecord* records = malloc(numOfRecords * sizeof(struct TrainScheduleRecord));
	getTrainSchedulesFromFile(records);

	struct TrainScheduleRecord returnSchedule = { 0 };
	for (int i = 0; i < numOfRecords; i++) {
		if (records[i].id == scheduleId) {
			returnSchedule = records[i];
			break;
		}
	}
	free(records);
	return returnSchedule;
}


bool removeTrainScheduleFromFile(int scheduleId) {
	FILE *filePtr = fopen("TrainSchedules.dat", "rb");
	if (filePtr == NULL) {
		fclose(filePtr);
		return false;
	}

	// read records into existingRecords struct pointer
	int numOfRecords = getNumberOfScheduleRecordsInFile();
	struct TrainScheduleRecord *existingRecords = malloc(numOfRecords * sizeof(struct TrainScheduleRecord));
	if (existingRecords == NULL) {
		fclose(filePtr);
		return false;
	}
	fread(existingRecords, sizeof(struct TrainScheduleRecord), numOfRecords, filePtr);
	fclose(filePtr);
	
	// create a new file to replace current file
	filePtr = fopen("TempTrainSchedules.dat", "wb");
	if (filePtr == NULL) {
		free(existingRecords);
		fclose(filePtr);
		return false;
	}

	for (int i = 0; i < numOfRecords; i++) {
		// skip writing if scheduleId match up
		if (existingRecords[i].id != scheduleId) 
			fwrite(&existingRecords[i], sizeof(struct TrainScheduleRecord), 1, filePtr);
	}
	fclose(filePtr);
	free(existingRecords);

	// delete old file and rename the new one to the same name to replace
	remove("TrainSchedules.dat");
	rename("TempTrainSchedules.dat", "TrainSchedules.dat");
	return true;
}


char* seatsBitFieldToGraphic(int seatsBitField) {
	// TODO convert seatBitField to binary

	char graphic[171] = "   A B   C D\n";

	for (int i = 1; i < 11; i++) {
		char row[15];
		sprintf(row, "%2d ", i);


		if (i == 5) strcat(row, "\n");
		strcat(graphic, row);
	}
}