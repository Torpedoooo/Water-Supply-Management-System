//
// Created by davidm-g on 16-03-2024.
//

#ifndef GRAPHPROJECT_RESERVOIR_H
#define GRAPHPROJECT_RESERVOIR_H

#include <string>

class Reservoir {
    private:
        std::string name;
        std::string municipality;
        int id;
        std::string code;
        int max_delivery;
    public:
        std::string get_name() const{
            return name;
        }
        void set_name(std::string name){
            this->name=name;
        }
        std::string get_municipality() const{
            return municipality;
        }
        void set_municipality(std::string mun){
            this->municipality=mun;
        }
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
        int get_max_delivery() const {
            return max_delivery;
        }

        void set_max_delivery(int max_delivery) {
            this->max_delivery = max_delivery;
        }
};


#endif //GRAPHPROJECT_RESERVOIR_H
