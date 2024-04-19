#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "TrainSchedulingModuleUtils.h"
#include "GeneralUtils.h"
#include "SystemEnums.h"


/**
 * For staff to schedule a train
 */
bool scheduleTrainMenu() {
	// record to be stored into TrainSchedules.dat
	struct TrainScheduleRecord newTrainScheduleRecord;
	// set record id to current timestamp
	newTrainScheduleRecord.id = getCurrentTimestamp();
	// initialize booked seats to 0
	newTrainScheduleRecord.seatsBitfield = 0;
	// to store user input for station selection
	int inputStation;


	// start getting schedule details
	system("cls");
	printf(
		"+------------------------+\n"
		"|  Schedule a Train:     |\n"
		"+------------------------+\n\n"
		"Please enter the details for the following.\n"
	);
	
	displayTrainStations();
	printf("Departure station: ");
	scanf(" %d", &inputStation);
	newTrainScheduleRecord.departureStation = (enum TrainStations)inputStation;

	printf("Arrival station: ");
	scanf(" %d", &inputStation);
	newTrainScheduleRecord.arrivalStation = (enum TrainStations)inputStation;

	printf("Departure date (dd/mm/yyyy): ");
	scanf(" %d/%d/%d", &newTrainScheduleRecord.departureDate.day, &newTrainScheduleRecord.departureDate.month, &newTrainScheduleRecord.departureDate.year);

	printf("Departure time (hh:mm): ");
	scanf(" %d:%d", &newTrainScheduleRecord.departureTime.hour, &newTrainScheduleRecord.departureTime.minute);

	printf("Arrival date (dd/mm/yyyy): ");
	scanf(" %d/%d/%d", &newTrainScheduleRecord.arrivalDate.day, &newTrainScheduleRecord.arrivalDate.month, &newTrainScheduleRecord.arrivalDate.year);

	printf("Arrival time (hh:mm): ");
	scanf(" %d:%d", &newTrainScheduleRecord.arrivalTime.hour, &newTrainScheduleRecord.arrivalTime.minute);
	

	// let user confirm details keyed in
	system("cls");
	printf("Schedule Record Details:\n");
	displayTrainScheduleMetadata(&newTrainScheduleRecord);

	char inputChoice;
	printf("\nPlease confirm the details entered (y/n): ");
	scanf(" %c", &inputChoice);
	if (!(inputChoice == 'y' || inputChoice == 'Y')) {
		// user does not confirm details
		printf("Canceled the scheduling process. You may re-enter the information.");
		system("pause");
		return false;
	}

	writeTrainScheduleToFile(&newTrainScheduleRecord);
	printf("Schedule is saved successfully.\n");
	system("pause");
	return true;
}

/**
 * Display train schedules in multi-page format
 */



void paginateTrainScheduleRecordsMenu() {
	int numOfRecords = getNumberOfScheduleRecordsInFile();
	struct TrainScheduleRecord *records = malloc(numOfRecords * sizeof(struct TrainScheduleRecord));
	getTrainSchedulesFromFile(&records);

	int currentPageIndex = 0, maxRecordPerPage = 4, maxPage = ceil(numOfRecords / 4.0);
	char userInput = 'a';

	while (1) {
		printf(
			"+------------------------+\n"
			"|  Train Schedules:      |\n"
			"+------------------------+\n"
		);

		int i = 0;
		while (i < maxRecordPerPage && (i + currentPageIndex * maxRecordPerPage) != (numOfRecords - 1)) {
			displayTrainScheduleMetadata(&records[i + currentPageIndex * maxRecordPerPage]);
			printf("++++++++++++++++++++++++++++++++++++++++++++\n");
			i++;
		}
		printf("\nPage %d / %d\n\n", currentPageIndex + 1, maxPage);
		printf("l = left, x = exit, r = right > ");
		userInput = getchar();

		// calculate user page control
		if ((userInput == 'l' || userInput == 'L') && currentPageIndex + 1 > 1) --currentPageIndex;
		else if ((userInput == 'r' || userInput == 'R') && currentPageIndex + 1 < maxPage) ++currentPageIndex;
		else if (userInput == 'x' || userInput == 'X') break;
		system("cls");
	}
	free(records);
}


/**
 * Remove a train schedule with given id
 */
void removeTrainScheduleRecordMenu() {
	int recordId;
	char confirmRemoval;
	printf(
		"+--------------------------------+\n"
		"|  Remove a Train Schedule:      |\n"
		"+--------------------------------+\n"
		"\nEnter the schedule id to be removed: "
	);
	scanf(" %d", &recordId);
	struct TrainScheduleRecord selectedSchedule = getTrainScheduleById(recordId);

	// specified schedule id not found
	if (selectedSchedule.id == 0) {
		printf("Could not find schedule with given id (%d).\n", recordId);
		system("pause");
		return;
	}

	// let user confirm before removing
	displayTrainScheduleMetadata(&selectedSchedule);
	printf("Confirm to remove this schedule? (y/n): ");
	scanf(" %c", &confirmRemoval);

	bool removeSuccess = removeTrainScheduleFromFile(recordId);

	if (removeSuccess) printf("Schedule record removed successfully.\n");
	else printf("Schedule records remove failed.\n");
	system("pause");
}