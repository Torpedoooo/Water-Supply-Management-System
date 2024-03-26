//
// Created by davidm-g on 16-03-2024.
//

#ifndef GRAPHPROJECT_NETWORK_H
#define GRAPHPROJECT_NETWORK_H

#include <string>
#include <unordered_map>
#include "data_structures/Graph.h"
#include "data_structures/Reservoir.h"
#include "data_structures/Station.h"
#include "data_structures/City.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <ctime>

class Network {
    private:
        Graph<std::string> graph;
        std::unordered_map<std::string,Vertex<std::string>*> vertices;
        std::unordered_map<std::string, Reservoir> reservoirs;
        std::unordered_map<std::string, City> cities;
        std::unordered_map<std::string, Station> stations;
        std::unordered_map<std::string,std::list<std::tuple<std::pair<std::string,std::string>,double,int>>> cities_impacted_by_pipes;

public:
    //Getters
    const Graph<std::string> &getGraph() const;

    //Parsing functions
    void parseCities(std::string path);
    void parseReservoirs(std::string path);
    void parseStations(std::string path);
    void parsePipes(std::string path);

    /////////////////////////
    void testAndVisit(std::queue< Vertex<std::string>*> &q, Edge<std::string> *e, Vertex<std::string> *w, double residual);
    bool findAugmentingPath(Graph<std::string> *g, Vertex<std::string> *s, Vertex<std::string> *t);
    double findMinResidualAlongPath(Vertex<std::string> *s, Vertex<std::string> *t);
    std::list<std::pair<std::string,double>> globalEdmondsKarp(Graph<std::string>g);
    void cityEdmondsKarp(std::string CityCode);
    void augmentFlowAlongPath(Vertex<std::string> *s, Vertex<std::string> *t, double f);
    std::list<std::pair<std::string,double>> calculate_water_needs(Graph<std::string>g);
    std::list<std::tuple<std::string,double,int>> vertex_out(std::string res_code, std::list<std::pair<std::string,double>> lista,Graph<std::string>g);
    std::list<std::string> findNonCriticalPumpingStations();
    std::list<std::pair<std::string,std::string>> getCriticalPipesForCity(std::string city_code);
    std::list<std::tuple<std::string,double,int>> pipe_out(std::string source_info,std::string target_info, std::list<std::pair<std::string,double>> lista, Graph<std::string> g);
    void pipe_out_impact(Graph<std::string> g);
    };


#endif //GRAPHPROJECT_NETWORK_H
