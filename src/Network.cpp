#include "Network.h"


void Network::parseCities(std::string path){
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << path << std::endl;
        return;
    }

    std::string firstLine;
    if (getline(file, firstLine)) { //read and ignore first line
    } else {
        std::cerr << "File is empty or missing header!" << std::endl;
        file.close();
        return;
    }
    //City,Id,Code,Demand,Population
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream linestream(line);
        std::string value;

        std::getline(linestream, value, ',');
        std::string city = value;

        std::getline(linestream, value, ',');
        int id = std::stoi(value);

        std::getline(linestream, value, ',');
        std::string code = value;

        std::getline(linestream, value, ',');
        double demand = std::stod(value);

        std::getline(linestream, value, ',');
        int population = std::stoi(value);

        City current_city;
        current_city.setCity(city);
        current_city.setId(id);
        current_city.setCode(code);
        current_city.setDemand(demand);
        current_city.setPopulation(population);
        cities[code] = current_city;
        graph.addVertex(code);
        vertices[code] = graph.findVertex(code);
        vertices[code]->setType(2);
    }
}


void Network::parseStations(std::string path){
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << path << std::endl;
        return;
    }

    std::string firstLine;
    if (getline(file, firstLine)) { //read and ignore first line
    } else {
        std::cerr << "File is empty or missing header!" << std::endl;
        file.close();
        return;
    }
    //Id,Code
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream linestream(line);
        std::string value;

        std::getline(linestream, value, ',');
        int id = std::stoi(value);

        std::getline(linestream, value, '\r');
        std::string code = value;

        Station station;
        station.setId(id);
        station.setCode(code);
        stations[code]=station;
        graph.addVertex(code);
        vertices[code] = graph.findVertex(code);
        vertices[code]->setType(1);
    }
}

void Network::parseReservoirs(std::string path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << path << std::endl;
        return;
    }

    std::string firstLine;
    if (getline(file, firstLine)) { //read and ignore first line
    } else {
        std::cerr << "File is empty or missing header!" << std::endl;
        file.close();
        return;
    }
    //Reservoir,Municipality,Id,Code,Maximum Delivery (m3/sec)
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream linestream(line);
        std::string value;

        std::getline(linestream, value, ',');
        std::string reservoir = value;

        std::getline(linestream, value, ',');
        std::string municipality = value;

        std::getline(linestream, value, ',');
        int id = std::stoi(value);

        std::getline(linestream, value, ',');
        std::string code = value;

        std::getline(linestream, value, ',');
        int max_delivery = std::stoi(value);

        Reservoir current_reservoir;
        current_reservoir.setCode(code);
        current_reservoir.setId(id);
        current_reservoir.set_name(reservoir);
        current_reservoir.set_municipality(municipality);
        current_reservoir.set_max_delivery(max_delivery);
        reservoirs[code]=current_reservoir;
        graph.addVertex(code);
        vertices[code] = graph.findVertex(code);
        vertices[code]->setType(0);
    }
}

void Network::parsePipes(std::string path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << path << std::endl;
        return;
    }

    std::string firstLine;
    if (getline(file, firstLine)) { //read and ignore first line
    } else {
        std::cerr << "File is empty or missing header!" << std::endl;
        file.close();
        return;
    }
    //Service_Point_A,Service_Point_B,Capacity,Direction
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream linestream(line);
        std::string value;

        std::getline(linestream, value, ',');
        std::string source = value;

        std::getline(linestream, value, ',');
        std::string dest= value;

        std::getline(linestream, value, ',');
        int capacity = std::stoi(value);

        std::getline(linestream, value, ',');
        int direction = std::stoi(value);

        if (direction == 1) {
            graph.addEdge(source, dest, capacity);
        } else {
            graph.addEdge(source,dest, capacity);
            graph.addEdge(dest,source, capacity);
        }
    }
}