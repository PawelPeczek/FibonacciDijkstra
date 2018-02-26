#ifndef DIJKSTRA_ON_FIBONACCI_HEAP_HEAP_H
#define DIJKSTRA_ON_FIBONACCI_HEAP_HEAP_H

#include "../Prototypes/Graph.h"

class MinPriorityQueue {
    Vertex **T; // Dynamic size array with amortized O(1)/op.
    int N; // number of elements currently in PriorityQueue
    int MaxSize; // MAX size of PriorityQueue
    int Left(int idx);
    int Right(int idx);
    int Parent(int idx);
    void MinHeapify(int idx); // return the index of heapified element
    void DecreaseKey(int idx, int new_key); // This operation is will not be used in standard Dijkstra
    void Enlarge();
    void Reduce();
public:
    MinPriorityQueue();
    MinPriorityQueue(int _n); // _n is the initial size of "dynamic-size" array T
    ~MinPriorityQueue();
    Vertex* Minimum();
    Vertex* Dequeue();
    bool Empty();
    void Enqueue(Vertex *e);
};

#endif //DIJKSTRA_ON_FIBONACCI_HEAP_HEAP_H
