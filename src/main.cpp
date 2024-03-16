//
// Created by davidm-g on 16-03-2024.
//
#include <iostream>
#include "Network.h"

int main() {
    Network network;
    network.parseCities("../src/dataset/small/Cities_Madeira.csv");
    network.parseReservoirs("../src/dataset/small/Reservoirs_Madeira.csv");
    network.parseStations("../src/dataset/small/Stations_Madeira.csv");
    network.parsePipes("../src/dataset/small/Pipes_Madeira.csv");
    return 0;
}