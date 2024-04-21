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

	printf("Price for the journey: RM");
	scanf(" %lf", &newTrainScheduleRecord.price);

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
	if (numOfRecords == 0) {
		printf(
			"+------------------------+\n"
			"|  Train Schedules:      |\n"
			"+------------------------+\n\n"
			"Currently empty.\n"
		);
		system("pause");
		return;
	}

	struct TrainScheduleRecord *records = malloc(numOfRecords * sizeof(struct TrainScheduleRecord));
	getTrainSchedulesFromFile(records);

	int currentPageIndex = 0, maxRecordPerPage = 4, maxPage = ceil(numOfRecords / 4.0);
	char userInput = 'a';

	while (1) {
		printf(
			"+------------------------+\n"
			"|  Train Schedules:      |\n"
			"+------------------------+\n"
		);

		int i = 0;
		while (i < maxRecordPerPage && (i + currentPageIndex * maxRecordPerPage) != numOfRecords) {
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
bool removeTrainScheduleRecordMenu() {
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

	while (1) {
		printf("Confirm to remove this schedule? (y/n): ");
		scanf(" %c", &confirmRemoval);

		if (confirmRemoval == 'y' || confirmRemoval == 'Y') break;
		if (confirmRemoval == 'n' || confirmRemoval == 'N') {
			printf("Canceled schedule removal.\n");
			system("pause");
			return;
		};
		printf("Invalid option.\n");
	}
	

	bool removeSuccess = removeTrainScheduleFromFile(recordId);

	if (removeSuccess) printf("Schedule record removed successfully.\n");
	else printf("Schedule records remove failed.\n");
	system("pause");
}


void chooseTrainScheduleSeatMenu(int scheduleId, int seatAmount, char *seatsSelectedInfo[4]) {
	struct TrainScheduleRecord trainScheduleData = getTrainScheduleById(scheduleId);
	char *seatsBinary = seatsBitFieldToBinary(trainScheduleData.seatsBitfield);
	
	printf(
		"+--------------------------------+\n"
		"|  Choose your seat(s):          |\n"
		"+--------------------------------+\n\n"
	);
	printSeatsGraphic(seatsBinary);

	for (int i = 0; i < seatAmount; i++) {
		char seatAlphabet;
		int seatNumber;
		printf("Select your seat %d (e.g. C8): ", i+1);
		scanf(" %c%d", &seatAlphabet, &seatNumber);
		seatAlphabet = tolower(seatAlphabet);
		
		if (seatAlphabet != 'a' && seatAlphabet != 'b' && seatAlphabet != 'c' && seatAlphabet != 'd') {
			printf("Invalid seat provided, seats are only from A - D.\n");
			--i;
			continue;
		}
		if (seatNumber < 1 || seatNumber > 10) {
			printf("Invalid seat provided, seats are only from 1 - 10.\n");
			--i;
			continue;
		}
		bool seatBookSuccess = bookTrainSeat(seatsBinary, seatAlphabet, seatNumber);
		if (!seatBookSuccess) {
			--i;
			continue;
		}

		// success
		sprintf(seatsSelectedInfo[i], "%c%d", seatAlphabet, seatNumber);
		system("cls");
		printSeatsGraphic(seatsBinary);
	}

	// let user confirm seat selection(s)
	char userOption;
	while (1) {
		printf("Confirm your seat selection? (y/n): ");
		scanf(" %c", &userOption);
		userOption = tolower(userOption);
		if (userOption == 'y') {
			trainScheduleData.seatsBitfield = seatsBinaryToBitField(seatsBinary);
			updateTrainScheduleRecordToFile(&trainScheduleData);
			printf("Confimed seat selection.\n");
			break;
		}
		else if (userOption == 'n') {
			printf("Canceled seat seletion.\n");
			break;
		}
		else printf("Invalid option.\n");
	}
	system("pause");
	free(seatsBinary);
}
