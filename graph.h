#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <utility>

class Node {
    std::pair<int, int> coords;
    map<pair<int, int>, Node*> neighbors;
public:
    Node(std::pair<int, int> coordinates): coords(coordinates){
        
    }
};

class Graph {
    
};

#endif
