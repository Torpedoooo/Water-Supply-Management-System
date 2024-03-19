//
// Created by davidm-g on 16-03-2024.
//
#include <iostream>
#include "Network.h"

int main() {
    Network network;
    network.parseCities("../src/dataset/large/Cities.csv");
    network.parseReservoirs("../src/dataset/large/Reservoir.csv");
    network.parseStations("../src/dataset/large/Stations.csv");
    network.parsePipes("../src/dataset/large/Pipes.csv");
    network.globalEdmondsKarp();
    std::cout << "---------------------\n";
    network.calculate_water_needs();
    auto lista = network.reservoir_out("R_1",network.calculate_water_needs());
    for (auto pair : lista) {
        std::cout << std::get<0>(pair) << " " << std::get<1>(pair) << " " << std::get<2>(pair) << std::endl;
    }
    return 0;
}