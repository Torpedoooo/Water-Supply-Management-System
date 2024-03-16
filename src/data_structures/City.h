//
// Created by davidm-g on 16-03-2024.
//

#ifndef GRAPHPROJECT_CITY_H
#define GRAPHPROJECT_CITY_H

#include <string>


class City {
private:
    int id;
    double demand;
    int population;
    std::string city;
    std::string code;

public:
    int getId() const {
        return id;
    }

    void setId(int id) {
        City::id = id;
    }

    double getDemand() const {
        return demand;
    }

    void setDemand(double demand) {
        City::demand = demand;
    }

    int getPopulation() const {
        return population;
    }

    void setPopulation(int population) {
        City::population = population;
    }

    const std::string &getCity() const {
        return city;
    }

    void setCity(const std::string &city) {
        this->city = city;
    }

    const std::string &getCode() const {
        return code;
    }

    void setCode(const std::string &code) {
        this->code = code;
    }
};


#endif //GRAPHPROJECT_CITY_H
