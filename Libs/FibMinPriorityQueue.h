#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

class FibMinPriorityQueue;
class FibonacciNode;

FibMinPriorityQueue* Union(FibMinPriorityQueue *H1, FibMinPriorityQueue *H2);

class FibMinPriorityQueue {
    FibonacciNode *Min;
    int N;
    void InsertToRootList(FibonacciNode *x);
    void Consolidate();
    void Link(FibonacciNode *y, FibonacciNode *x);
    void DeleteFromRootList(FibonacciNode *y);
    void AddToChildList(FibonacciNode *parent, FibonacciNode *new_child);
    void Cut(FibonacciNode *x, FibonacciNode *y);
    void Cascading(FibonacciNode *y);
    void DeleteFromChildList(FibonacciNode *parent, FibonacciNode *child);
    void DestructHeap(FibonacciNode *root, int lvl);
public:
    FibMinPriorityQueue();
    FibonacciNode* Enqueue(int key, int _vert_idx);
    FibonacciNode* Minimum();
    FibonacciNode* Dequeue();
    bool Empty();
    void DecreaseKey(FibonacciNode* elem, int new_key);
    void DeleteKey(FibonacciNode* elem);
    ~FibMinPriorityQueue();

    static void Swap(FibonacciNode **x, FibonacciNode **y);
    static void ConcatenateLists(FibonacciNode *L1, FibonacciNode *L2);

    friend FibMinPriorityQueue* Union(FibMinPriorityQueue* H1, FibMinPriorityQueue* H2);
};


class FibonacciNode {
    int Degree;
    bool Mark;
    FibonacciNode *Parent;
    FibonacciNode *Child;
    FibonacciNode *Left;
    FibonacciNode *Right;
    int Key;
    int VertexIdx;
public:
    FibonacciNode(int _key);
    int GetVrtIdx();
    void SetVrtIdx(int _idx);
    int GetKey();
    void SetKet(int _key);

    friend class FibMinPriorityQueue;
    friend FibMinPriorityQueue* Union(FibMinPriorityQueue* H1, FibMinPriorityQueue* H2);
};

#endif //FIBONACCIHEAP_H
