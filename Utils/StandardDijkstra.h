#ifndef DIJKSTRA_ON_FIBONACCI_HEAP_STANDARDDIJKSTRA_H
#define DIJKSTRA_ON_FIBONACCI_HEAP_STANDARDDIJKSTRA_H


#include "../Prototypes/Graph.h"

class StandardDijkstra {
public:
    static void FindShortestPaths(Graph *G, int s);
    static void PrintPath(Graph *G, int d);
};


#endif //DIJKSTRA_ON_FIBONACCI_HEAP_STANDARDDIJKSTRA_H
