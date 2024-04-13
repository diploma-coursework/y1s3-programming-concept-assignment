#include <stdio.h>
#include <time.h>
#include "GeneralStructs.h"

void displayTrainStations() {
    printf(
        "0 - Tokyo\n"
        "1 - Nagoya\n"
        "2 - Kanazawa\n"
        "3 - Kyoto\n"
        "4 - Shin-Osaka\n"
        "5 - Ueno\n"
        "6 - Shin-Yokohama\n"
        "7 - Odawara\n"
        "8 - Okayama\n"
        "9 - Sendai\n"
        "10 - Tsurumai\n"
        "11 - Akihabara\n\n"
    );
}

int getCurrentTimestamp() {
    time_t currentTime;
    time(&currentTime);

    return (int)currentTime;
}