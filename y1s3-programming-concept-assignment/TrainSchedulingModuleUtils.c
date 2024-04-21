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


char* seatsBitFieldToBinary(int seatsBitField) {
	// X = 1, O = 0
	char *seatsBinary = malloc(41 * sizeof(char));
	for (int i = 0; i < 40; i++) {
		if ((seatsBitField >> (39 - i)) & 1) seatsBinary[i] = 'X';
		else seatsBinary[i] = 'O';
	}
	return seatsBinary;
}

void printSeatsGraphic(char *seatsBinary) {
	// create the graphic by interpreting the binary
	char graphic[172] = "   A B   C D\n";
	for (int i = 0; i < 10; i++) {
		char row[15];
		sprintf(
			row, 
			"%2d %c %c   %c %c\n", 
			i+1, 
			seatsBinary[i * 4], 
			seatsBinary[i * 4 + 1],
			seatsBinary[i * 4 + 2],
			seatsBinary[i * 4 + 3]
		);

		if (i == 4) strcat(row, "\n");
		strcat(graphic, row);
	}
	strcat(graphic, "\nX = Booked, O = Available\n");
	printf("%s", graphic);
}

bool bookTrainSeat(char *seatsBinary, char seatAlphabet, int seatNumber) {
	int seatAlphabetValue = (int)seatAlphabet - 97; // ASCII value of 'a' is 97, adjust to get a = 0, b = 1 so on
	int seatIndex = 4 * (seatNumber - 1) + seatAlphabetValue;

	if (seatsBinary[seatIndex] == 'X') {
		printf("Seat is already taken. Please choose another seat.\n");
		return false;
	}
	seatsBinary[seatIndex] = 'X';
	return true;
}

int seatsBinaryToBitField(char* seatsBinary) {
	int result = 0;
	for (int i = 0; i < 40; i++) {
		result = (result << 1) | (seatsBinary[i] == 'X');
	}
	return result;
}

void updateTrainScheduleRecordToFile(struct TrainScheduleRecord *scheduleRecord) {
	removeTrainScheduleFromFile(scheduleRecord->id);
	scheduleRecord->seatsBitfield = 0;
	writeTrainScheduleToFile(scheduleRecord);
}