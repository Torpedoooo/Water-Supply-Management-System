//
// Created by ruiborges on 26-03-2024.
//

#ifndef GRAPHPROJECT_UTILS_H
#define GRAPHPROJECT_UTILS_H

#include "Network.h"

bool reservoir_exists(Network &network, std::string reservoir_code);
bool city_exists(Network &network, std::string city_code);
bool station_exists(Network &network, std::string station_code);

#endif //GRAPHPROJECT_UTILS_H
