#include "Menu.h"
#include <limits>

void showMetrics(Network network);
void showGlobaledmondsKarp(Network network);
void showReliability(Network network);

void showMenu(Network network){
    system("clear");
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << " ┏ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺  ┓" << "\n";
    std::cout << "                Menu" << "\n";
    std::cout << " ┗ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺┛" << "\n";
    std::cout << "1. Service Metrics" << "\n";
    std::cout << "2. Reliability and sensitivity to failures" << "\n";
    std::cout << "3. Exit" << "\n";
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;

    while (std::cin.fail() || choice>3|| choice <1){
        std::cout << "Invalid choice. Please try again." << "\n";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cout << "Enter your choice: ";
        std::cin >> choice;
    }

    switch (choice){
        case 1:
            showMetrics(network);
            break;

        case 2:
            showReliability(network);
            break;

        case 3:
            std::cout << "Exiting..." << "\n";
            return;

        default:
            std::cout << "Invalid choice. Please try again." << "\n";
            break;
    }
}


void showGlobaledmondsKarp(Network network){
    system("clear");
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << " ┏ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺  ┓" << "\n";
    std::cout << "                Flows" << "\n";
    std::cout << " ┗ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺┛" << "\n";
    auto lista = network.globalEdmondsKarp(network.getGraph());
    int total = 0;
    for (auto &i : lista) {
        std::cout << i.first << " " << i.second << std::endl;
        total += i.second;
    }
    std::cout << "Total flow: " << total << std::endl;
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << "Press any key to go back to the menu." << "\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    showMetrics(network);

}

void showCityEdmondsKarp(Network network, std::string city){
    system("clear");
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << " ┏ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺  ┓" << "\n";
    std::cout << "            "<< city <<" Flow" << "\n";
    std::cout << " ┗ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺┛" << "\n";
    network.cityEdmondsKarp(city);
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << "Press any key to go back to the menu." << "\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    showMetrics(network);
}

void showWaterNeeds(Network network){
    system("clear");
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << " ┏ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺  ┓" << "\n";
    std::cout << "                Water Needs" << "\n";
    std::cout << " ┗ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺┛" << "\n";
    auto lista = network.calculate_water_needs(network.getGraph());
    for (auto &i : lista) {
        std::cout << i.first;
        if (i.second < 0){
            std::cout << " needs more " << std::abs(i.second) << " m^3 of water." << "\n";
        } else {
            std::cout << " does not need water" << "\n";
        }
    }
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << "Press any key to go back to the menu." << "\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    showMetrics(network);
}


void showMetrics(Network network){
    system("clear");
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << " ┏ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺  ┓" << "\n";
    std::cout << "                Menu" << "\n";
    std::cout << " ┗ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺┛" << "\n";
    std::cout << "1. General Max-Flow" << "\n";
    std::cout << "2. Max-Flow for city" << "\n";
    std::cout << "3. Water Needs" << "\n";
    std::cout << "4. Go back" << "\n";
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << "Enter your choice: ";
    int choice;
    std::cin.clear();
    std::cin.ignore(256,'\n');
    std::cin >> choice;

    while (std::cin.fail() || choice>4|| choice <1){
        std::cout << "Invalid choice. Please try again." << "\n";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cout << "Enter your choice: ";
        std::cin >> choice;
    }

    std::string city;

    switch (choice){
        case 1:
            showGlobaledmondsKarp(network);
            break;

        case 2:
            std::cout << "Enter the city code: ";
            std::cin >> city;
            while (std::cin.fail()){
                std::cout << "Invalid choice. Please try again." << "\n";
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cout << "Enter the city code: ";
                std::cin >> city;
            }
            showCityEdmondsKarp(network, city);
            break;

        case 3:
            showWaterNeeds(network);
            break;

        case 4:
            showMenu(network);
            break;

        default:
            std::cout << "Invalid choice. Please try again." << "\n";
            break;
    }
}

void showReservoirOut(Network network, std::string reservoir){
    system("clear");
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << " ┏ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺  ┓" << "\n";
    std::cout << "         "<< reservoir <<" Impact" << "\n";
    std::cout << " ┗ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺┛" << "\n";
    auto lista = network.vertex_out(reservoir,network.calculate_water_needs(network.getGraph()),network.getGraph());
    for (auto &i : lista) {
       if (std::get<2>(i) == 1){
           std::cout << std::get<0>(i) << " met demand and now doesn't. It lost " << std::abs(std::get<1>(i)) << " m^3 of water." << "\n";
       } else if (std::get<2>(i) == 2){
           if (std::get<1>(i)==0){
               std::cout << std::get<0>(i) << " wasn't impacted by the reservoir being out." << "\n";
           } else if (std::get<1>(i) < 0){
               std::cout << std::get<0>(i) << " met demands and still meets, but lost:  " << std::abs(std::get<1>(i)) << " m^3 of water." << "\n";
           }
       } else if (std::get<2>(i) == 3){
           if (std::get<1>(i)==0){
               std::cout << std::get<0>(i) << " wasn't impacted by the reservoir being out." << "\n";
           }else if (std::get<1>(i) < 0){
           std::cout << std::get<0>(i) << " didn't meet demands and still doesnt and lost: " << std::abs(std::get<1>(i)) << " m^3 of water." << "\n";
           }
       }
    }
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << "Press any key to go back to the menu." << "\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    showReliability(network);
}

void showPumpingStationMaintenance(Network network, std::string station) {
    system("clear");
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << " ┏ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺  ┓" << "\n";
    std::cout << "         "<< station <<" Impact" << "\n";
    std::cout << " ┗ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺┛" << "\n";
    auto lista = network.vertex_out(station,network.calculate_water_needs(network.getGraph()),network.getGraph());
    for (auto &i : lista) {
        if (std::get<2>(i) == 1){
            std::cout << std::get<0>(i) << " met demand and now doesn't. It lost " << std::abs(std::get<1>(i)) << " m^3 of water." << "\n";
        } else if (std::get<2>(i) == 2){
            if (std::get<1>(i)==0){
                std::cout << std::get<0>(i) << " wasn't impacted by the reservoir being out." << "\n";
            } else if (std::get<1>(i) < 0){
                std::cout << std::get<0>(i) << " met demands and still meets, but lost:  " << std::abs(std::get<1>(i)) << " m^3 of water." << "\n";
            }
        } else if (std::get<2>(i) == 3){
            if (std::get<1>(i)==0){
                std::cout << std::get<0>(i) << " wasn't impacted by the reservoir being out." << "\n";
            }else if (std::get<1>(i) < 0){
                std::cout << std::get<0>(i) << " didn't meet demands and still doesnt and lost: " << std::abs(std::get<1>(i)) << " m^3 of water." << "\n";
            }
        }
    }
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << "Press any key to go back to the menu." << "\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    showReliability(network);
}

void showCriticalPipesForCity(Network network, std::string city) {
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << " ┏ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺  ┓" << "\n";
    std::cout << "   Pipes than impact " << city << "\n";
    std::cout << " ┗ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺┛" << "\n";
    auto lista = network.getCriticalPipesForCity(city);
    for (auto &i : lista) {
        std::cout << "The failure of the pipe from " << std::get<0>(i) << " to " << std::get<1>(i) << " causes a loss of " << std::abs(std::get<2>(i)) << " m^3." << "\n";
    }
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << "Press any key to go back to the menu." << "\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    showReliability(network);
}



void showReliability(Network network) {
    system("clear");
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << " ┏ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺  ┓" << "\n";
    std::cout << "                Menu" << "\n";
    std::cout << " ┗ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺ ╺┛" << "\n";
    std::cout << "1. Reservoir out" << "\n";
    std::cout << "2. Pumping Station Maintenance" << "\n";
    std::cout << "3. Critical Pipes for City" << "\n";
    std::cout << "4. Go back" << "\n";
    std::cout << " ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡" << "\n";
    std::cout << "Enter your choice: ";
    int choice;
    std::cin.clear();
    std::cin.ignore(256, '\n');
    std::cin >> choice;

    while (std::cin.fail() || choice > 4 || choice < 1) {
        std::cout << "Invalid choice. Please try again." << "\n";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Enter your choice: ";
        std::cin >> choice;
    }
    std::string reservoir;
    std::string station;
    std::string city;

    switch(choice) {
        case 1:
            std::cout << "Enter the reservoir code: ";
            std::cin.clear();
            std::cin >> reservoir;
            while (std::cin.fail() || !reservoir_exists(network,reservoir)){
                std::cout << "Invalid choice. Please try again." << "\n";
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cout << "Enter the reservoir code: ";
                std::cin >> reservoir;
            }
            showReservoirOut(network,reservoir);
            break;
        case 2:
            std::cout << "Enter the station code: ";
            std::cin.clear();
            std::cin >> station;
            while (std::cin.fail() || !station_exists(network, station)){
                std::cout << "Invalid choice. Please try again." << "\n";
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cout << "Enter the station code: ";
                std::cin >> station;
            }
            showPumpingStationMaintenance(network,station);
            break;
        case 3:
            std::cout << "Enter the city code: ";
            std::cin.clear();
            std::cin >> city;
            while (std::cin.fail() || !city_exists(network, city)){
                std::cout << "Invalid choice. Please try again." << "\n";
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cout << "Enter the city code: ";
                std::cin >> city;
            }
            showCriticalPipesForCity(network,city);
            break;
        case 4:
            showMenu(network);
            break;
        default:
            std::cout << "Invalid choice. Please try again." << "\n";
            break;
    }
}