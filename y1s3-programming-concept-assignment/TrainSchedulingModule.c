#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

	system("cls");
	printf(
		"Schedule a Train\n"
		"================\n\n"
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

	displayTrainScheduleMetadata(&newTrainScheduleRecord);

	return true;
}