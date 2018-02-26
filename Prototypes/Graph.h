#ifndef DIJKSTRA_ON_FIBONACCI_HEAP_GRAPH_H
#define DIJKSTRA_ON_FIBONACCI_HEAP_GRAPH_H

#include "../Libs/FibMinPriorityQueue.h"


class ListNode{
    ListNode *Next;
    int V;
    int W;
public:
    ListNode(int _v, int _w);
    ListNode* GetNext();
    int GetV();
    int GetW();

    friend class ExtendedDijkstra;
    friend class StandardDijkstra;
    friend class Graph;
    friend class Vertex;
};

class Vertex{
    FibonacciNode *Reference;
    int IdxInVrtxTable;
public:
    int D;
    int Parent;
    bool Processed;
    ListNode *Adj;
    Vertex();
    void AddReference(FibonacciNode *ref);
    void AddReference(int idx);
    ~Vertex();

    friend class Graph;
    friend class StandardDijkstra;
    friend class ExtendedDijkstra;
};

class Graph {
    Vertex **Vertices;
    int N;
public:
    int GetN();
    Vertex* & operator[](int el) {return Vertices[el];}
    Graph(int _n);
    void InsertAdj(int u, int _v, int _w);
    ~Graph();

    friend class StandardDijkstra;
    friend class ExtendedDijkstra;
};


#endif //DIJKSTRA_ON_FIBONACCI_HEAP_GRAPH_H
