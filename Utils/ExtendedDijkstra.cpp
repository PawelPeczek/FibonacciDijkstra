#include "ExtendedDijkstra.h"
#include <cstdlib>
#include <climits>
#include <iostream>
#include "../Libs/FibMinPriorityQueue.h"

void ExtendedDijkstra::FindShortestPaths(Graph *G, int s) {
    (*G)[s]->Parent = s;
    (*G)[s]->D = 0;
    FibMinPriorityQueue *Q = new FibMinPriorityQueue();
    for (int i = 0; i < G->N; ++i) {
        (*G)[i]->AddReference(Q->Enqueue((*G)[i]->D, i));
    }
    while(!Q->Empty()){
        FibonacciNode *u = Q->Dequeue();
        int u_vId = u->GetVrtIdx();
        if((*G)[u_vId]->Processed) continue;
        (*G)[u_vId]->Processed = true;
        for(ListNode *v = (*G)[u_vId]->Adj; v != NULL; v = v->Next){
            if((*G)[u_vId]->D != INT_MAX && (*G)[u_vId]->D + v->W < (*G)[v->V]->D){
                (*G)[v->V]->Parent = u_vId;
                (*G)[v->V]->D = (*G)[u_vId]->D + v->W;
                Q->DecreaseKey((*G)[v->V]->Reference, (*G)[v->V]->D);
            }
        }
    }
    delete Q;
}
