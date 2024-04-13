#include <stdio.h>
#include <time.h>
#include "SystemEnums.h"
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

void displayTrainStations(enum TrainStations trainStation) {
    switch (trainStation) {
        case tokyo:
            printf("Tokyo");
            break;
        case nagoya:
            printf("Nagoya");
            break;
        case kanazawa:
            printf("Kanazawa");
            break;
        case kyoto:
            printf("Kyoto");
            break;
        case shinosaka:
            printf("Shin-Osaka");
            break;
        case ueno:
            printf("Ueno");
            break;
        case shinyokohama:
            printf("Shin-Yokohama");
            break;
        case odawara:
            printf("Odawara");
            break;
        case okayama:
            printf("Okayama");
            break;
        case sendai:
            printf("Sendai");
            break;
        case tsurumai:
            printf("Tsurumai");
            break;
        case akihabara:
            printf("Akihabara");
            break;
    }
}


int getCurrentTimestamp() {
    time_t currentTime;
    time(&currentTime);

    return (int)currentTime;
}