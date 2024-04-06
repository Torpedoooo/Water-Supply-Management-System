//
// Created by davidm-g on 16-03-2024.
//
#include <iostream>
#include "Network.h"
#include "Menu.h"

int main() {
    Network network;
    network.parseCities("../src/dataset/large/Cities.csv");
    network.parseReservoirs("../src/dataset/large/Reservoir.csv");
    network.parseStations("../src/dataset/large/Stations.csv");
    network.parsePipes("../src/dataset/large/Pipes.csv");
    network.pipe_out_impact(network.getGraph());
    Menu menu;
    menu.showMenu(network);

    return 0;
}