#include <iostream>

#include "utils.h"

bool reservoir_exists(Network &network, std::string reservoir_code){
    for (auto &reservoir : network.getReservoirs()){
        if (reservoir.first == reservoir_code){
            return true;
        }
    }
    return false;
}

bool city_exists(Network &network, std::string city_code){
    for (auto &city : network.getCities()){
        if (city.first == city_code){
            return true;
        }
    }
    return false;
}

bool station_exists(Network &network, std::string station_code){
    for (auto &station : network.getStations()){
        if (station.first == station_code){
            return true;
        }
    }
    return false;
}

bool pipe_exists( Network &network,  std::pair<std::string, std::string> pipe){
    for (const auto &p : network.getPipes()){
        if (p.first == pipe.first && p.second == pipe.second){
            return true;
        }
    }
    return false;
}