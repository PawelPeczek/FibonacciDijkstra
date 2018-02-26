#include "Graph.h"
#include <cstdlib>
#include <climits>

ListNode::ListNode(int _v, int _w){
    Next = NULL;
    V = _v;
    W = _w;
}

ListNode* ListNode::GetNext() {
    return Next;
}

int ListNode::GetV() {
    return V;
}

int ListNode::GetW() {
    return W;
}

Vertex::Vertex() {
    Reference = NULL;
    D = INT_MAX;
    Processed = false;
    Adj = NULL;
    Parent = -1; // No parent found
}

void Vertex::AddReference(FibonacciNode *ref) {
    Reference = ref;
}

void Vertex::AddReference(int idx) {
    IdxInVrtxTable = idx;
}

Vertex::~Vertex() {
    while(Adj != NULL){
        ListNode *q = Adj;
        Adj = Adj->Next;
        delete q;
    }
}

Graph::Graph(int _n) {
    N = _n;
    Vertices = new Vertex* [N];
    for (int i = 0; i < N; ++i) {
        Vertices[i] = new Vertex();
        Vertices[i]->AddReference(i);
    }
}

int Graph::GetN() {
    return N;
}

void Graph::InsertAdj(int u, int _v, int _w) {
    ListNode *new_elem = new ListNode(_v, _w);
    if(Vertices[u]->Adj == NULL) Vertices[u]->Adj = new_elem;
    else{
        new_elem->Next = Vertices[u]->Adj;
        Vertices[u]->Adj = new_elem;
    }
}

Graph::~Graph() {
    for (int i = 0; i < N; ++i) {
        delete Vertices[i];
    }
    delete[] Vertices;
}


