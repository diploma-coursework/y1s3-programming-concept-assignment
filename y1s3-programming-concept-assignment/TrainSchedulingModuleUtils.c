#include <stdio.h>
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