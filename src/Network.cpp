#include <cfloat>
#include "Network.h"
#include <list>
#include <map>

const Graph<std::string> &Network::getGraph() const {
    return graph;
}


void Network::parseCities(std::string path){
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << path << std::endl;
        return;
    }

    std::string firstLine;
    if (getline(file, firstLine)) { //read and ignore first line
    } else {
        std::cerr << "File is empty or missing header!" << std::endl;
        file.close();
        return;
    }
    //City,Id,Code,Demand,Population
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream linestream(line);
        std::string value;

        std::getline(linestream, value, ',');
        std::string city = value;

        std::getline(linestream, value, ',');
        int id = std::stoi(value);

        std::getline(linestream, value, ',');
        std::string code = value;

        std::getline(linestream, value, ',');
        double demand = std::stod(value);

        std::getline(linestream, value, ',');
        int population = std::stoi(value);

        City current_city;
        current_city.setCity(city);
        current_city.setId(id);
        current_city.setCode(code);
        current_city.setDemand(demand);
        current_city.setPopulation(population);
        cities[code] = current_city;
        graph.addVertex(code);
        vertices[code] = graph.findVertex(code);
        vertices[code]->setType(2);

    }
}


void Network::parseStations(std::string path){
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << path << std::endl;
        return;
    }

    std::string firstLine;
    if (getline(file, firstLine)) { //read and ignore first line
    } else {
        std::cerr << "File is empty or missing header!" << std::endl;
        file.close();
        return;
    }
    //Id,Code
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream linestream(line);
        std::string value;

        std::getline(linestream, value, ',');
        int id = std::stoi(value);

        std::getline(linestream, value, '\r');
        std::string code = value;

        Station station;
        station.setId(id);
        station.setCode(code);
        stations[code]=station;
        graph.addVertex(code);
        vertices[code] = graph.findVertex(code);
        vertices[code]->setType(1);
    }
}

void Network::parseReservoirs(std::string path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << path << std::endl;
        return;
    }

    std::string firstLine;
    if (getline(file, firstLine)) { //read and ignore first line
    } else {
        std::cerr << "File is empty or missing header!" << std::endl;
        file.close();
        return;
    }
    //Reservoir,Municipality,Id,Code,Maximum Delivery (m3/sec)
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream linestream(line);
        std::string value;

        std::getline(linestream, value, ',');
        std::string reservoir = value;

        std::getline(linestream, value, ',');
        std::string municipality = value;

        std::getline(linestream, value, ',');
        int id = std::stoi(value);

        std::getline(linestream, value, ',');
        std::string code = value;

        std::getline(linestream, value, ',');
        int max_delivery = std::stoi(value);

        Reservoir current_reservoir;
        current_reservoir.setCode(code);
        current_reservoir.setId(id);
        current_reservoir.set_name(reservoir);
        current_reservoir.set_municipality(municipality);
        current_reservoir.set_max_delivery(max_delivery);
        reservoirs[code]=current_reservoir;
        graph.addVertex(code);
        vertices[code] = graph.findVertex(code);
        vertices[code]->setType(0);
    }
}

void Network::parsePipes(std::string path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << path << std::endl;
        return;
    }

    std::string firstLine;
    if (getline(file, firstLine)) { //read and ignore first line
    } else {
        std::cerr << "File is empty or missing header!" << std::endl;
        file.close();
        return;
    }
    //Service_Point_A,Service_Point_B,Capacity,Direction
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream linestream(line);
        std::string value;

        std::getline(linestream, value, ',');
        std::string source = value;

        std::getline(linestream, value, ',');
        std::string dest= value;

        std::getline(linestream, value, ',');
        int capacity = std::stoi(value);

        std::getline(linestream, value, ',');
        int direction = std::stoi(value);

        if (direction == 1) {
            graph.addEdge(source, dest, capacity);
        } else {
            graph.addEdge(source,dest, capacity);
            graph.addEdge(dest,source, capacity);
        }
    }

}

void Network::testAndVisit(std::queue< Vertex<std::string>*> &q, Edge<std::string> *e, Vertex<std::string> *w, double residual) {
// Check if the vertex 'w' is not visited and there is residual capacity
    if (! w->isVisited() && residual > 0) {
// Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e); //confirm that vertex w is reached through edge e
        q.push(w);
    }
}
// Function to find an augmenting path using Breadth-First Search
bool Network::findAugmentingPath(Graph<std::string> *g, Vertex<std::string> *s, Vertex<std::string> *t) {
// Mark all vertices as not visited
    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
// Mark the source vertex as visited and enqueue it
    s->setVisited(true);
    std::queue<Vertex<std::string> *> q;
    q.push(s);
// BFS to find an augmenting path
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
// Process outgoing edges
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
// Process incoming edges
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow()); //process residual edges
        }
    }
// Return true if a path to the target is found, false otherwise
    return t->isVisited();
}
// Function to find the minimum residual capacity along the augmenting path
double Network::findMinResidualAlongPath(Vertex<std::string> *s, Vertex<std::string> *t) { //find bottleneck
    double f = INF;
// Traverse the augmenting path to find the minimum residual capacity
    for (auto v = t; v != s; ) {
        auto e = v->getPath(); //check the edge associated wih the vertex
        if (e->getDest() == v) { //forward edge, the edge is pointing to v
            f = std::min(f, e->getWeight() - e->getFlow()); //residual capacity is c(u,v)-f(u,v)
            v = e->getOrig(); //next vertex to see is the one that got to v
        }
        else { //residual edge
            f = std::min(f, e->getFlow()); //residual capacity is the value of the residual edge
            v = e->getDest(); //next vertex to see is the one that v is pointing to
        }
    }
// Return the minimum residual capacity
    return f;
}
// Function to augment flow along the augmenting path with the given flow value

void Network::augmentFlowAlongPath(Vertex<std::string> *s, Vertex<std::string> *t, double f) {
// Traverse the augmenting path and update the flow values accordingly
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {  //if not residual edge
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else { //if residual edge
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}
//0: Reservoir / 1: Station / 2:City
std::list<std::pair<std::string,double>> Network::globalEdmondsKarp(Graph<std::string> g, bool output = false) {
    g.addVertex("SS");
    g.addVertex("ST");

    for (Vertex<std::string> *v : g.getVertexSet()) {
        if (v->getType() == 0) {
            g.addEdge("SS", v->getInfo(), reservoirs[v->getInfo()].get_max_delivery());
        }
        else if (v->getType() == 2) {
            g.addEdge(v->getInfo(), "ST", cities[v->getInfo()].getDemand());
        }
    }

// Find source and target vertices in the graph
    Vertex<std::string>* s = g.findVertex("SS");
    Vertex<std::string>* t = g.findVertex("ST");
// Validate source and target vertices
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
// Initialize flow on all edges to 0
    for (auto v : g.getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
// While there is an augmenting path, augment the flow along the path
    while( findAugmentingPath(&g, s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
    std::list<std::pair<std::string,double>> lista;


    if (output) {
        std::ostringstream path_out;

        std::time_t tw = std::time(0);   // get time now
        std::tm *now = std::localtime(&tw);
        path_out << "../output/maxflow-" << now->tm_hour << "-" << now->tm_min << "-" << now->tm_mday << "-"
                 << now->tm_mon + 1 << "-" << now->tm_year + 1900 << ".csv";
        std::string out_path = path_out.str();

        std::ofstream file(out_path.c_str());

        file << "City,Code,WaterReceived\n";
        for (Edge<std::string> *e: t->getIncoming()) {
            file << cities[e->getOrig()->getInfo()].getCity() <<
                 "," << cities[e->getOrig()->getInfo()].getCode() <<
                 "," << e->getFlow() << "\n";
        }
        file.close();
    }

    for (Edge<std::string> *e: t->getIncoming()) {
        lista.emplace_back(e->getOrig()->getInfo(), e->getFlow());
    }

    g.removeVertex("SS");
    g.removeVertex("ST");

    return lista;
}
//0: Reservoir / 1: Station / 2:City


std::pair<std::string,double> Network::cityEdmondsKarp(std::string CityCode) {
    Graph<std::string> g = this->graph;
    Vertex<std::string>* target_city = vertices[CityCode];
    g.addVertex("SS");
    g.addVertex("ST");

    for (Vertex<std::string> *v : g.getVertexSet()) {
        if (v->getType() == 0) {
            g.addEdge("SS", v->getInfo(), reservoirs[v->getInfo()].get_max_delivery());
        }
        else if (v==target_city) {
            g.addEdge(v->getInfo(), "ST", cities[v->getInfo()].getDemand());
        }
    }

// Find source and target vertices in the graph
    Vertex<std::string>* s = g.findVertex("SS");
    Vertex<std::string>* t = g.findVertex("ST");
// Validate source and target vertices
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
// Initialize flow on all edges to 0
    for (auto v : g.getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
// While there is an augmenting path, augment the flow along the path
    while( findAugmentingPath(&g, s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
    std::pair<std::string,double> par;
    for(Edge<std::string> *e : t->getIncoming()) {

        par =  make_pair(e->getOrig()->getInfo(),e->getFlow());
    }
    g.removeVertex("SS");
    g.removeVertex("ST");
    return par;
}


std::list<std::pair<std::string,double>> Network::calculate_water_needs(Graph<std::string> g){
    std::list<std::pair<std::string,double>> lista = globalEdmondsKarp(g);
    std::list<std::pair<std::string,double>> return_list;
    for (auto pair : lista) {
         double met_demand = pair.second - cities[pair.first].getDemand(); //if negative, it means that the city is not receiving enough water
         return_list.emplace_back(pair.first,met_demand);
    }
    return return_list;
}


//List of tuples: City, WaterReceived, MetDemand
std::list<std::tuple<std::string,double,int>> Network::vertex_out(std::string res_code, std::list<std::pair<std::string,double>> lista, Graph<std::string> g){
    Vertex<std::string>* vertex = graph.findVertex(res_code);
    if (vertex == nullptr) {
        throw std::logic_error("Vertex not found");
    }

    std::map<Edge<std::string>*, double> original_weights;
    std::map<Edge<std::string>*, double> original_flows;
    for (auto edge : vertex->getAdj()) {
        original_weights[edge] = edge->getWeight();
        original_flows[edge] = edge->getFlow();
        edge->setWeight(0);
        edge->setFlow(0);
    }
    for (auto edge : vertex->getIncoming()) {
        original_weights[edge] = edge->getWeight();
        original_flows[edge] = edge->getFlow();
        edge->setWeight(0);
        edge->setFlow(0);
    }

    auto new_list = calculate_water_needs(g);
    std::list<std::tuple<std::string,double,int>> return_list;
    for (auto pair : new_list){
        auto it = std::find_if(lista.begin(), lista.end(), [&pair](const std::pair<std::string,double>& element){ return element.first == pair.first; });
        if(it != lista.end()){
            if (it->second>=0 && pair.second<0){
                return_list.emplace_back(pair.first,pair.second-it->second,1); // 1 If met demand and now doesnt
            }
            else if (it->second>=0 && pair.second>=0){
                return_list.emplace_back(pair.first,pair.second-it->second,2); // 2 If met demand and still does
            }
            else if (it->second<0 && pair.second<0){
                return_list.emplace_back(pair.first,pair.second-it->second,3); // 3 If not met demand and still doesnt
            }
            else if (it->second<0 && pair.second>=0){
                return_list.emplace_back(pair.first,pair.second-it->second,4); // 4 If not met demand and now does
            }
        }
    }

    for (auto edge : vertex->getAdj()) {
        edge->setWeight(original_weights[edge]);
        edge->setFlow(original_flows[edge]);
    }
    for (auto edge : vertex->getIncoming()) {
        edge->setWeight(original_weights[edge]);
        edge->setFlow(original_flows[edge]);
    }

    return return_list;
}

std::list<std::string> Network::findNonCriticalPumpingStations(){
    std::list<std::string> non_critical_stations;
    auto current_edmonds_list = calculate_water_needs(graph);
    for (auto station : stations){

        Vertex<std::string>* station_vertex = graph.findVertex(station.first);
        if (station_vertex == nullptr) {
            continue;
        }

        std::map<Edge<std::string>*, double> original_weights;
        std::map<Edge<std::string>*, double> original_flows;
        for (auto edge : station_vertex->getAdj()) {
            original_weights[edge] = edge->getWeight();
            original_flows[edge] = edge->getFlow();
            edge->setWeight(0);
            edge->setFlow(0);
        }
        for (auto edge : station_vertex->getIncoming()) {
            original_weights[edge] = edge->getWeight();
            original_flows[edge] = edge->getFlow();
            edge->setWeight(0);
            edge->setFlow(0);
        }

        auto new_list = calculate_water_needs(graph);
        if (std::equal(new_list.begin(), new_list.end(), current_edmonds_list.begin())) {
            non_critical_stations.push_back(station.first);
        }

        for (auto edge : station_vertex->getAdj()) {
            edge->setWeight(original_weights[edge]);
            edge->setFlow(original_flows[edge]);
        }
        for (auto edge : station_vertex->getIncoming()) {
            edge->setWeight(original_weights[edge]);
            edge->setFlow(original_flows[edge]);
        }
    }
    return non_critical_stations;
}

void Network::pipe_out_impact(Graph<std::string> g){
    auto initial_needs = calculate_water_needs(g);

    for (Vertex<std::string> *v : g.getVertexSet()) {
        for (Edge<std::string> *e: v->getAdj()) {
            e->setSelected(false);
        }
    }

    for (Vertex<std::string> *v : g.getVertexSet()){
        for (Edge<std::string > *e : v->getAdj()){
            if (!e->isSelected()){
                e->setSelected(true);
                double original_weight = e->getWeight();
                double original_flow = e->getFlow();
                e->setWeight(0);
                e->setFlow(0);
                auto new_list = calculate_water_needs(g);
                //Compare the new list with the initial list, add the pipes with respective impacts as a value to the key city in the map, the second value is the difference beetween previous and current water received using the same tags 1,2,3,4 as above the edge doesnt need to come from the city
                for (auto pair : new_list){
                    auto it = std::find_if(initial_needs.begin(), initial_needs.end(), [&pair](const std::pair<std::string,double>& element){ return element.first == pair.first; });
                    if(it != initial_needs.end()){
                        if (it->second>=0 && pair.second<0){
                            cities_impacted_by_pipes[pair.first].emplace_back(std::make_tuple(std::make_pair(v->getInfo(),e->getDest()->getInfo()),pair.second-it->second,1));
                        }
                        else if (it->second>=0 && pair.second>=0){
                            cities_impacted_by_pipes[pair.first].emplace_back(std::make_tuple(std::make_pair(v->getInfo(),e->getDest()->getInfo()),pair.second-it->second,2));
                        }
                        else if (it->second<0 && pair.second<0 && pair.second<it->second){
                            cities_impacted_by_pipes[pair.first].emplace_back(std::make_tuple(std::make_pair(v->getInfo(),e->getDest()->getInfo()),pair.second-it->second,3));

                        }
                        else if (it->second<0 && pair.second>=0 ){
                            cities_impacted_by_pipes[pair.first].emplace_back(std::make_tuple(std::make_pair(v->getInfo(),e->getDest()->getInfo()),pair.second-it->second,4));
                        }
                    }
                }

                e->setWeight(original_weight);
                e->setFlow(original_flow);
            }
        }
    }
}

std::list<std::tuple<std::string,std::string,double,int>> Network::getCriticalPipesForCity(std::string city_code){
    std::list<std::tuple<std::string,std::string,double,int>> critical_pipes;
    for (auto pipe : cities_impacted_by_pipes[city_code]){
        if (std::get<2>(pipe) == 1 || std::get<2>(pipe) == 3){
            critical_pipes.emplace_back(std::get<0>(pipe).first,std::get<0>(pipe).second,std::get<1>(pipe),std::get<2>(pipe));
        }
    }
    return critical_pipes;
}

const std::unordered_map<std::string, Reservoir> &Network::getReservoirs() const {
    return reservoirs;
}

const std::unordered_map<std::string, City> &Network::getCities() const {
    return cities;
}

const std::unordered_map<std::string, Station> &Network::getStations() const {
    return stations;
}

const std::unordered_map<std::string, std::list<std::tuple<std::pair<std::string, std::string>, double, int>>> &
Network::getCitiesImpactedByPipes() const {
    return cities_impacted_by_pipes;
}
