//
// Created by davidm-g on 16-03-2024.
//

#ifndef GRAPHPROJECT_CITY_H
#define GRAPHPROJECT_CITY_H

#include <string>

class City {

private:
    int id;
    int demand;
    int population;
    std::string City;
    std::string Code;

public:
    int getId() const {
        return id;
    }

    void setId(int id) {
        City::id = id;
    }

    int getDemand() const {
        return demand;
    }

    void setDemand(int demand) {
        City::demand = demand;
    }

    int getPopulation() const {
        return population;
    }

    void setPopulation(int population) {
        City::population = population;
    }

    const std::string &getCity() const {
        return City;
    }

    void setCity(const std::string &city) {
        City = city;
    }

    const std::string &getCode() const {
        return Code;
    }

    void setCode(const std::string &code) {
        Code = code;
    }
};


#endif //GRAPHPROJECT_CITY_H
