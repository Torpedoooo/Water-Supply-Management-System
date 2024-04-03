//
// Created by davidm-g on 16-03-2024.
//
#include <iostream>
#include "Network.h"
#include "Menu.h"

int main() {
    Network network;
    network.parseCities("../src/dataset/small/Cities_Madeira.csv");
    network.parseReservoirs("../src/dataset/small/Reservoirs_Madeira.csv");
    network.parseStations("../src/dataset/small/Stations_Madeira.csv");
    network.parsePipes("../src/dataset/small/Pipes_Madeira.csv");
    network.pipe_out_impact(network.getGraph());
    showMenu(network);

    /*std:: cout << "---------------------\n";
    auto lista2 = network.vertex_out("PS_55",network.calculate_water_needs(network.getGraph()),network.getGraph());
    for (auto &i : lista2) {
        std::cout << std::get<0>(i) << " " << std::get<1>(i) << " " << std::get<2>(i) << std::endl;
    }

    std:: cout << "---------------------\n";
    auto lista3 = network.vertex_out("PS_55",network.calculate_water_needs(network.getGraph()),network.getGraph());
    for (auto &i : lista3) {
        std::cout << std::get<0>(i) << " " << std::get<1>(i) << " " << std::get<2>(i) << std::endl;
    }

    std::cout << "---------------------\n";
    auto lista4 = network.globalEdmondsKarp(network.getGraph());
    for (auto &i : lista4) {
        std::cout << i.first << " " << i.second << std::endl;
    }

    std::cout << "---------------------\n";
    auto lista5=network.getCriticalPipesForCity("C_1");
    for (auto &i : lista5) {
        std::cout << i.first << " " << i.second << std::endl;
    }*/

    return 0;
}