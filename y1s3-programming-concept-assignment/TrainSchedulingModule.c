#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "GeneralStructs.h"
#include "GeneralUtils.h"
#include "SystemEnums.h"

struct TrainScheduleRecord {
	int id;
	struct Date departureDate;
	struct Time departureTime;
	struct Date arrivalDate;
	struct Time arrivalTime;
	enum TrainStations departureStation;
	enum TrainStations arrivalStation;
};

/**
 * For staff to schedule a train
 */
bool scheduleTrainMenu() {
	struct TrainScheduleRecord newTrainScheduleRecord;

	system("cls");
	printf(
		"Schedule a Train\n"
		"================\n\n"
		"Please enter the details for the following.\n"
	);

	displayTrainStations();
	printf("Departure station: ");
	scanf(" %d", newTrainScheduleRecord.departureStation);


	printf("Arrival station: ");
	scanf(" %d", newTrainScheduleRecord.arrivalStation);

	return true;
}