#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "GeneralStructs.h"
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
bool scheduleTrain() {
	struct TrainScheduleRecord newTrainScheduleRecord;

	printf("Schedule a Train\n");
	printf("Day of arrival (dd/mm/yyyy): ");
	scanf(" %d/%d/%d");
}