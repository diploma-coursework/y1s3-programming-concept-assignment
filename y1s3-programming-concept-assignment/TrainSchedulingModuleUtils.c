#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "GeneralUtils.h"
#include "TrainSchedulingModuleUtils.h"


void displayTrainScheduleMetadata(struct TrainScheduleRecord *record) {
	printf("Schedule Record Details:\n");
	printf("ID: %d\n", (*record).id);

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

bool writeTrainScheduleToFile(struct TrainScheduleRecord* record) {
	FILE* filePtr = fopen("TrainSchedules.dat", "wb");
	if (filePtr == NULL) {
		return false;
	}
	fwrite(record, sizeof(struct TrainScheduleRecord), 1, filePtr);
	fclose(filePtr);
	return true;
}

void debugPrintTrainScheduleFromFile() {
	FILE* filePtr = fopen("TrainSchedules.dat", "rb");
	if (filePtr == NULL) {
		printf("Error opening file for reading.\n");
		return;
	}

	struct TrainScheduleRecord record;
	while (fread(&record, sizeof(struct TrainScheduleRecord), 1, filePtr) == 1) {
		displayTrainScheduleMetadata(&record);
		printf("%d\n", record.id);
	}

	fclose(filePtr);
	// Pause the program until user presses Enter
	printf("Press Enter to continue...");
	while (getchar() != '\n');
}