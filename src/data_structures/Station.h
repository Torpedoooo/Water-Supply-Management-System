//
// Created by davidm-g on 16-03-2024.
//

#ifndef GRAPHPROJECT_STATION_H
#define GRAPHPROJECT_STATION_H
#include <string>


class Station {
    private:
        int id;
        std::string code;
    public:
    int getId() const {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

    const std::string &getCode() const {
        return code;
    }

    void setCode(const std::string &code) {
        this->code;
    }
};


#endif //GRAPHPROJECT_STATION_H
