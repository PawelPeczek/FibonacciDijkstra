#include "MinPriorityQueue.h"

#include <iostream>
#include <climits>

int MinPriorityQueue::Left(int i) {
    return 2 * i + 1;
}

int MinPriorityQueue::Right(int i) {
    return 2 * i + 2;
}

int MinPriorityQueue::Parent(int i) {
    return (i - 1) / 2;
}

MinPriorityQueue::MinPriorityQueue() : MinPriorityQueue::MinPriorityQueue(50){}

MinPriorityQueue::MinPriorityQueue(int max_size) {
    T = new Vertex *[max_size + 1]; // One element more -> to not overflow when enqueueing every vertex.
    MaxSize = max_size + 1;
    N = 0;
}

MinPriorityQueue::~MinPriorityQueue() {
    delete[] T;
}

Vertex* MinPriorityQueue::Minimum() {
    return T[0];
}

Vertex* MinPriorityQueue::Dequeue() {
    Vertex* RES = T[0];
    std::swap(T[0], T[N - 1]);
    N--;
    MinHeapify(0);
    if(N < (MaxSize / 4) && MaxSize >= 128) Reduce(); // Not to reduce very small tables -> only when more than ~100 slots are free
    return RES;
}

bool MinPriorityQueue::Empty() {
    return N == 0;
}

void MinPriorityQueue::MinHeapify(int idx) {
    int l = Left(idx);
    int r = Right(idx);
    int min = idx;
    if(l < N && T[l]->D < T[idx]->D) min = l;
    if(r < N && T[r]->D < T[min]->D) min = r;
    if(min != idx){
        std::swap(T[idx], T[min]);
        MinHeapify(min);
    }
}

void MinPriorityQueue::DecreaseKey(int idx, int new_key) {
    // only if this operation makes sense
    if(T[idx]->D > new_key){
        T[idx]->D = new_key;
        // while T[idx] is not a root of heap and MinHeap constrains are violated
        while(idx > 0 && T[Parent(idx)]->D > T[idx]->D){
            std::swap(T[idx], T[Parent(idx)]);
            idx = Parent(idx);
        }
    }
}

void MinPriorityQueue::Enqueue(Vertex *e) {
    T[N] = e;
    int _d_tmp = e->D;
    T[N]->D = INT_MAX;
    DecreaseKey(N, _d_tmp);
    N++; // N always indicates the "next slot to insert".
    if(N == MaxSize) Enlarge();
}

void MinPriorityQueue::Enlarge() {
    Vertex **TMP = new Vertex *[MaxSize * 2];
    for (int i = 0; i < N; ++i) {
        TMP[i] = T[i];
    }
    MaxSize *= 2;
    delete[] T;
    T = TMP;
}

void MinPriorityQueue::Reduce() {
    Vertex **TMP = new Vertex *[MaxSize / 2];
    for (int i = 0; i < N; ++i) {
        TMP[i] = T[i];
    }
    MaxSize/= 2;
    delete[] T;
    T = TMP;
}

