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

const char* trainStationToString(enum TrainStations trainStation) {
    switch (trainStation) {
        case TOKYO: return "Tokyo";
        case NAGOYA: return "Nagoya";
        case KANAZAWA: return "Kanazawa";
        case KYOTO: return "Kyoto";
        case SHINOSAKA: return "Shin-Osaka";
        case UENO: return "Ueno";
        case SHINYOKOHAMA: return "Shin-Yokohama";
        case ODAWARA: return "Odawara";
        case OKAYAMA: return "Okayama";
        case SENDAI: return "Sendai";
        case TSURUMAI: return "Tsurumai";
        case AKIHABARA: return "Akihabara";
        default: return "Invalid";
    }
}

int getCurrentTimestamp() {
    time_t currentTime;
    time(&currentTime);

    return (int)currentTime;
}

