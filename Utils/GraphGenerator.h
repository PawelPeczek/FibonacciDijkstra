#ifndef DIJKSTRA_ON_FIBONACCI_HEAP_GRAPHGENERATOR_H
#define DIJKSTRA_ON_FIBONACCI_HEAP_GRAPHGENERATOR_H

#include "../Prototypes/Graph.h"

class TwinGraphs {
public:
    Graph *G1, *G2;
    TwinGraphs(int _n);
    ~TwinGraphs();
};

class GraphGenerator {
public:
    static TwinGraphs* GenerateTwinGraphs(int V, int avg_adj_edg);
    static void PrintGeneratedGraph(Graph *G);
};


#endif //DIJKSTRA_ON_FIBONACCI_HEAP_GRAPHGENERATOR_H
