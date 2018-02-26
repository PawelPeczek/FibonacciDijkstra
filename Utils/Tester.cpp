#include <ctime>
#include <iostream>
#include "Tester.h"
#include "../Prototypes/Graph.h"
#include "./StandardDijkstra.h"
#include "./ExtendedDijkstra.h"
#include "./GraphGenerator.h"


void Tester::MakeTest() {

    int V, E_per_Vrtx;
    printf("*********************************************************\n");
    printf("*\tDijkstra algorithm implementation tester\t*\n");
    printf("*********************************************************\n\n\n");

    printf("This program was created to measure efficiency different implementation of Dijkstra algorithm. ");
    printf("First version is implemented based on standard priority queue and the second one - based on Fibonacci Heap.\n");

    do{
        printf("Please enter the number of vertexes (V) in random generated graph: ");
        scanf("%i", &V);
        if(V <= 1){
            printf("The number of vertexes is to small. Try again with number above 1.\n");
        }
    } while(V <= 1);

    do{
        printf("Please enter the number of adjacent vertices for each vertex in random generated graph. ");
        printf("Point, that parallel edges are forbidden - so that valid value is from range [1, V - 1]: ");
        scanf("%i", &E_per_Vrtx);
        if(E_per_Vrtx < 1 || E_per_Vrtx >= V){
            printf("The number of adjacent vertices is to small. Try again with number above 1.\n");
        }
    } while(E_per_Vrtx < 1 || E_per_Vrtx >= V);

    try {
        printf("Generating random graphs... (This may take a while in case of big numbers of vertices and/or edges)\n");
        TwinGraphs *A = GraphGenerator::GenerateTwinGraphs(V, E_per_Vrtx);
        printf("Graphs generated!\n");
        printf("Test start!\n");
        const clock_t b1 = clock();
        int rand_val = rand() % V;
        StandardDijkstra::FindShortestPaths(A->G1, 1);
        printf("Test 1. (standard heap) done!\n");
        StandardDijkstra::PrintPath(A->G1, V - 1 - rand_val);
        printf("\nExecution time (in clock ticks): %i\n", clock() - b1);
        const clock_t b2 = clock();
        ExtendedDijkstra::FindShortestPaths(A->G2, 1);
        printf("Test 2. (FibonacciHeap)\n");
        StandardDijkstra::PrintPath(A->G2, V - 1 - rand_val);
        printf("\nExecution time (in clock ticks): %i\n", clock() - b2);
        printf("All tests done!\n");
    } catch(std::bad_alloc& ex){
        printf("The memory was exhausted. Try with smaller graph :(\n");
    }
}