//
// Created by ruiborges on 26-03-2024.
//

#ifndef GRAPHPROJECT_MENU_H
#define GRAPHPROJECT_MENU_H
#include "Network.h"
#include "utils.h"
class Menu {
    public:
        /**
         * Function to show initial menu
         * @param network that includes all the data
         */
        void showMenu(Network network);
        /**
         * Function to show all cities flow and total flow
         * @param network that includes all the data
         */
        void showGlobaledmondsKarp(Network network);
        /**
         * Function that shows the flow of a specific given city
         * @param network that includes all the data
         * @param city whose flow is printed
         */
        void showCityEdmondsKarp(Network network, std::string city);
        /**
         * Function to show the water needs of all cities
         * @param network that includes all the data
         */
        void showWaterNeeds(Network network);
        /**
         * Function that shows original and balanced metrics of the network
         * @param network that includes all the data
         */
        void showMetricsBeforeAndAfterBalancing(Network network);
        /**
         * Function to show basic metrics menu
         * @param network that includes all the data
         */
        void showMetrics(Network network);
        /**
         * Function that shows impact of removing a station or a reservoir
         * @param network that includes all the data
         * @param reservoir or station code to remove
         */
        void showReservoirOut(Network network, std::string reservoir);
        /**
         * Function that shows pumping stations that can be removed without impact on cities' flows
         * @param network that includes all the data
         */
        void showPumpingStationMaintenance(Network network);
        /**
         * Function that shows the critical pipes for a given city
         * @param network that includes all the data
         * @param city whose critical pipes are returned
         */
        void showCriticalPipesForCity(Network network, std::string city);
        /**
         * Function that shows the impact of removing a list of given pipes
         * @param network that includes all the data
         * @param pipes that are removed
         */
        void showPipesOut(Network network, std::list<std::pair<std::string, std::string>> pipes);
        /**
         * Function to show reliability and sensitivity to failures menu
         * @param network that includes all the data
         */
        void showReliability(Network network);
};

#endif //GRAPHPROJECT_MENU_H
