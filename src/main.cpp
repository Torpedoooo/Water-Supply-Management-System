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
    network.pipe_out_impact(network.getGraph());


    auto lista=network.calculate_water_needs(network.getGraph());
    for (auto &i : lista) {
        std::cout << i.first << " " << i.second << std::endl;
    }
    std::cout << "---------------------\n";
    auto lista5=network.getCriticalPipesForCity("C_17");
    for (auto &i : lista5) {
        std::cout << i.first << " " << i.second << std::endl;
    }


    return 0;
}