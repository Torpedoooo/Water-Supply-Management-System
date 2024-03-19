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
    std::cout << "---------------------\n";
    auto lista = network.findNonCriticalPumpingStations();
    for (auto &i : lista) {
        std::cout << i << std::endl;
    }

    std:: cout << "---------------------\n";
    auto lista2 = network.vertex_out("PS_66",network.calculate_water_needs(network.getGraph()),network.getGraph());
    for (auto &i : lista2) {
        std::cout << std::get<0>(i) << " " << std::get<1>(i) << " " << std::get<2>(i) << std::endl;
    }
    return 0;
}