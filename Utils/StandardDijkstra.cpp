#include "StandardDijkstra.h"
#include "../Libs/MinPriorityQueue.h"
#include <iostream>
#include <climits>


void StandardDijkstra::FindShortestPaths(Graph *G, int s) {
    (*G)[s]->Parent = s;
    (*G)[s]->D = 0;
    MinPriorityQueue *Q = new MinPriorityQueue(G->N);
    Q->Enqueue((*G)[s]);
    while(!Q->Empty()){
        Vertex *u = Q->Dequeue();
        if(u->Processed) continue;
        u->Processed = true;
        for(ListNode *v = u->Adj; v != NULL; v = v->Next){
            if(u->D != INT_MAX && u->D + v->W < (*G)[v->V]->D){
                (*G)[v->V]->Parent = u->IdxInVrtxTable;
                (*G)[v->V]->D = u->D + v->W;
                Q->Enqueue((*G)[v->V]);
            }
        }
    }
    delete Q;
}

void StandardDijkstra::PrintPath(Graph *G, int d){
    if((*G)[d]->Parent == -1){
        printf("Path doesn't exist!\n");
        return;
    }
    if((*G)[d]->Parent == d){
        printf("%i ", d);
        return;
    }
    PrintPath(G, (*G)[d]->Parent);
    printf("-> %i (d: %i)", d, (*G)[d]->D);
}