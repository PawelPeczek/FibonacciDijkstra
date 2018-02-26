#include "GraphGenerator.h"
#include <random>
#include <ctime>
#include <climits>

TwinGraphs::TwinGraphs(int N) {
    G1 = new Graph(N);
    G2 = new Graph(N);
}

TwinGraphs::~TwinGraphs() {
    delete G1;
    delete G2;
}

TwinGraphs* GraphGenerator::GenerateTwinGraphs(int V, int avg_adj_edg) { // avg_adj_edg -> from O(1) to O(V)
    srand(time(NULL));
    TwinGraphs *RES = new TwinGraphs(V);
    int **T = new int *[V];
    for(int i = 0; i < V; i++) T[i] = new int[V];
    // Creating a matrix of adjacency
    for(int i = 0; i < V; i++){
        int adj_left = avg_adj_edg;
        for (int j = 0; j < V; j++) {
            if(i == j) T[i][j] = 0; // No loops allowed
            else {
                if(adj_left == 0) T[i][j] = INT_MAX; // No edge
                else {
                    // Must be an edge here -> V-1 is the max allowed avg_adj_edg || May be the edge here
                    if((j >= i && V - j == adj_left) || (j < i && V - j == adj_left + 1) || rand() % 42  < 21) {
                        T[i][j] = 1 + rand() % 13;
                        adj_left--;
                    } else T[i][j] = INT_MAX; // No edge
                }

            }
        }
    }
    // Creating graph (adj. list) from matrix
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j ++){
            if(T[i][j] != 0 && T[i][j] != INT_MAX){
                RES->G1->InsertAdj(i, j, T[i][j]);
                RES->G2->InsertAdj(i, j, T[i][j]);
            }
        }
    }
    for(int i = 0; i < V; i++) delete[] T[i];
    delete[] T;
    return RES;
}

/*
 * Debugging function
 */
void GraphGenerator::PrintGeneratedGraph(Graph *G) {
    for(int i = 0; i < G->GetN(); i++){
        printf("V%i\t adj: ", i);
        for(ListNode *it = (*G)[i]->Adj; it != NULL; it = it->GetNext()) printf("%i(%i) -> ", it->GetV(), it->GetW());
        printf("NULL\n");
    }
}