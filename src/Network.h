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
#include <set>


class Network {
    private:
        Graph<std::string> graph;
        std::unordered_map<std::string,Vertex<std::string>*> vertices;
        std::unordered_map<std::string, Reservoir> reservoirs;
    std::unordered_map<std::string, City> cities;
        std::unordered_map<std::string, Station> stations;
    std::set<std::pair<std::string, std::string>> pipes;
        std::unordered_map<std::string,std::list<std::tuple<std::pair<std::string,std::string>,double,int>>> cities_impacted_by_pipes;

public:
    //Getters
    /**
     * @brief Getter for the network's graph - 0(1)
     * @return Returns the network's graph
     */
    const Graph<std::string> &getGraph() const;

    /**
     * Getter for the network's reservoir map. - 0(1)
     * @return Returns the network's reservoir map.
     */
    const std::unordered_map<std::string, Reservoir> &getReservoirs() const;

    /**
     * Getter for the network's cities map. - 0(1)
     * @return Returns the network's cities map.
     */
    const std::unordered_map<std::string, City> &getCities() const;

    /**
     * Getter for the network's stations map. - 0(1)
     * @return Returns the network's stations map.
     */
    const std::unordered_map<std::string, Station> &getStations() const;

    /**
     * Getter for the network's pipes set. - 0(1)
     * @return Returns the network's pipes set.
     */
    const std::set<std::pair<std::string, std::string>> &getPipes() const;

    const std::unordered_map<std::string, std::list<std::tuple<std::pair<std::string, std::string>, double, int>>> &
    getCitiesImpactedByPipes() const;

    //Parsing functions

    /**
     * @brief Function to parse the cities file - 0(n * V)
     * @param path that points to the cities file
     */
    void parseCities(std::string path);

    /**
     * Function to parse the reservoirs file - O(n * V)
     * @param path that points to the reservoirs file
     */
    void parseReservoirs(std::string path);

    /**
     * Function to parse the stations file - O(n * V)
     * @param path that points to the stations file
     */
    void parseStations(std::string path);

    /**
     * Function to parse the pipes file - O(n * V)
     * @param path that points to the pipes file
     */
    void parsePipes(std::string path);

    /**
     * This function is used within the BFS algorithm to test whether a vertex w is not visited and
     * if there is residual capacity available in an edge e.
     * If both conditions are met, it marks the vertex w as visited, sets the path through which it was reached,
     * and enqueues it for further exploration. - 0(1)
     *
     * @param q queue of vertices
     * @param e edge to test
     * @param w vertex to visit
     * @param residual value used for the conditions
     */
    void testAndVisit(std::queue< Vertex<std::string>*> &q, Edge<std::string> *e, Vertex<std::string> *w, double residual);
    /**
     *  This function implements the Breadth-First Search (BFS) algorithm to find an augmenting path in a graph.
     *  It starts from a given source vertex s and explores the graph until it reaches the target vertex t
     *  or until there are no more unvisited vertices reachable from the source vertex s. - 0(V + E)
     *
     * @param g the provided graph
     * @param s source node
     * @param t target node
     * @return Return true if a path to the target is found, false otherwise
     */
    bool findAugmentingPath(Graph<std::string> *g, Vertex<std::string> *s, Vertex<std::string> *t);
    /**
     * This function calculates the minimum residual capacity along the augmenting path found by the BFS algorithm.
     * It traverses the augmenting path from the target vertex t back to the source vertex s,
     * considering both forward and backward edges. - 0(E)
     * @param s source vertex
     * @param t target vertex
     * @return returns the minimum residual capacity found.
     */
    double findMinResidualAlongPath(Vertex<std::string> *s, Vertex<std::string> *t);

    /**
     * Performs an Edmonds-Karp algorithm to determine the maximum amount of water that can reach each city
     * writes the output to a file - O(V * E²)
     * @param g the provided graph
     * @param output boolean to determine if the output should be written to a file
     * @return a list of pairs (city code, value)
     */
    std::list<std::pair<std::string,double>> globalEdmondsKarp(Graph<std::string>g, bool output);
    /**
     * Performs a balanced Edmonds-Karp algorithm to determine the maximum amount of water that can reach each city
     * - O(V * E²)
     * @param g the provided graph
     * @param output boolean to determine if the output should be written to a file
     * @return a list of pairs (city code, value)
     */
    std::list<std::pair<std::string,double>> balancedEdmondsKarp(Graph<std::string> g, bool output);
    /**
     * This function calculates the metrics of the network, such as the total flow, the total flow that reaches the cities,
     * and the total flow that reaches the reservoirs. - O(E)
     * @param g the network's graph
     * @return a tuple with the metrics
     */
    std::tuple<double, double, double> computeMetricsBalanced(Graph<std::string> g);
     /**
     * This function calculates the metrics of the network, such as the total flow, the total flow that reaches the cities,
     * and the total flow that reaches the reservoirs. - O(E)
     * @param g the network's graph
     * @return a tuple with the metrics
     */
    std::tuple<double, double, double> computeMetrics(Graph<std::string> g);
    /**
     * Performs an Edmonds-Karp algorithm to determine the maximum amount of water that can reach a specific city - O(V * E²)
     * @param CityCode the city to analyse
     * @return a pair with CityCode and the amount of water received
     */
    std::pair<std::string,double> cityEdmondsKarp(std::string CityCode);
    /**
     * This function is responsible for augmenting the flow along the augmenting path with the given flow value f.
     * It traverses the augmenting path from the target vertex t back to the source vertex s,
     * updating the flow values of the edges accordingly based on the direction of the edges. - O(E)
     * @param s source vertex
     * @param t target vertex
     * @param f flow value to augment along path
     */
    void augmentFlowAlongPath(Vertex<std::string> *s, Vertex<std::string> *t, double f);

    /**
     * This function calculates the water received per city vs its demand
     * if a negative value --> demand not being met - O(V * E²)
     * @param g the network's graph
     * @return a list of pairs (city code, value)
     */
    std::list<std::pair<std::string,double>> calculate_water_needs(Graph<std::string>g);

    /**
     * This function takes a vertex received by input out of the graph
     * and compares the water all the cities receive, prior and after the said removal - O(V * E²)
     * @param res_code code of the vertex to remove
     * @param lista list of pairs (city code, value) of the original water received
     * @param g the network's graph
     * @return a list of tuples(City, WaterReceived, MetDemand)
     */
    std::list<std::tuple<std::string,double,int>> vertex_out(std::string res_code, std::list<std::pair<std::string,double>> lista,Graph<std::string>g);

    /**
     * Calculates which pumping stations can be temporarily removed
     * without affecting the delivery capacity to all the cities - O((V * E²) * V)
     * @return a list with the codes of the non critical pumping stations
     */
    std::list<std::string> findNonCriticalPumpingStations();

    /**
     * Function to access the results generated by pipe_out_impact() to a specific city - O(n)
     * @param city_code of the city to analyse
     * @return the pipes, which ruptured, would make it impossible
     * to deliver the desired amount of water to the city_code
     */
    std::list<std::tuple<std::string,std::string,double,int>> getCriticalPipesForCity(std::string city_code);
    /**
     * Function to calculate impact that each pipe has on each city.
     * This function is called only once, since for each iteration (for each pipe in the graph),
     * the cities affected by the said pipe are stored in a map, making it unnecessary to iterate through
     * all edges for each and every city. - O( (V * E²) * E)
     * @param g the network's graph
     */
    void pipe_out_impact(Graph<std::string> g);

    /**
     * Function to calculate the impact of removing a pipe on the network - O(V * E³)
     * @param pipes list of pairs (pipe code, pipe name) to remove
     * @param lista list of pairs (city code, value) of the original water received
     * @param g the network's graph
     * @return a list of tuples(City, WaterReceived, MetDemand)
     */
    std::list<std::tuple<std::string,double,int>> pipe_out(std::list<std::pair<std::string,std::string>> pipes, std::list<std::pair<std::string,double>> lista, Graph<std::string> g);
    };


#endif //GRAPHPROJECT_NETWORK_H
