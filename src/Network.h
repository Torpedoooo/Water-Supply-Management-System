//
// Created by davidm-g on 16-03-2024.
//

#ifndef GRAPHPROJECT_NETWORK_H
#define GRAPHPROJECT_NETWORK_H

#include <string>
#include <unordered_map>
#include "data_structures/Graph.h"
#include "data_structures/Reservoir.h"
#include "data_structures/Station.h"
#include "data_structures/City.h"
#include <iostream>
#include <fstream>
#include <sstream>

class Network {
    private:
        Graph<std::string> graph;
        std::unordered_map<std::string,Vertex<std::string>*> vertices;
        std::unordered_map<std::string, Reservoir> reservoirs;
        std::unordered_map<std::string, City> cities;
        std::unordered_map<std::string, Station> stations;

public:

    //Parsing functions
    void parseCities(std::string path);
    void parseReservoirs(std::string path);
    void parseStations(std::string path);
    void parsePipes(std::string path);
    /////////////////////////
};


#endif //GRAPHPROJECT_NETWORK_H
