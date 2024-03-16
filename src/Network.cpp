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
        graph.findVertex(code)->setType(2);
    }
}
