//
// Created by ruiborges on 26-03-2024.
//

#ifndef GRAPHPROJECT_MENU_H
#define GRAPHPROJECT_MENU_H
#include "Network.h"
#include "utils.h"
class Menu {
    public:
        void showMenu(Network network);
        void showGlobaledmondsKarp(Network network);
        void showCityEdmondsKarp(Network network, std::string city);
        void showWaterNeeds(Network network);
        void showMetricsBeforeAndAfterBalancing(Network network);
        void showMetrics(Network network);
        void showReservoirOut(Network network, std::string reservoir);
        void showPumpingStationMaintenance(Network network);
        void showCriticalPipesForCity(Network network, std::string city);
        void showPipesOut(Network network, std::list<std::pair<std::string, std::string>> pipes);
        void showReliability(Network network);
};

#endif //GRAPHPROJECT_MENU_H
