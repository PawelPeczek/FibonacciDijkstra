#include "./FibMinPriorityQueue.h"
#include <cmath>
#include <climits>
#include <cstdlib>
#include <iostream>

/*
 * I assume that basic idea of FibonacciHeap is known - so that only
 * specific operation on cyclic doubly-linked-list will be explained.
 * For details of FibonacciHeap: see Introduction to algorithms by Cormen
 */


FibMinPriorityQueue* Union(FibMinPriorityQueue *H1, FibMinPriorityQueue *H2){
    FibMinPriorityQueue *H = new FibMinPriorityQueue();
    H->Min = H1->Min;
    FibMinPriorityQueue::ConcatenateLists(H->Min, H2->Min);
    if(H1->Min == NULL || (H2->Min != NULL && H2->Min->Key < H1->Min->Key)){
        H->Min = H2->Min;
    }
    H->N = H1->N + H2->N;
    return H;
}

/*
 * General function for cyclic doubly-linked-list
 * While swapping two FibonacciNode we must swap them on root/children list
 * which is basically doubly-linked-list.
 * There are some specific cases (shown simplifications but works even if ex. A = B):
 * 1) * <-> A <-> x <-> y <-> B <->... <-> *
 *      In this situation we must change:
 *      B->left to x;
 *      A->right to y;
 *      y->left to A;
 *      x->right to B;
 *      y->right to x;
 *      x->left to y;
 *   * <-> A <-> y <-> x <-> B <->... <-> *
 *   Special sub-case is now * <-> x <-> y <-> * but this then nothing must be done.
 *
 * 2) (symmetric to one) * <-> A <-> y <-> x <-> B <->... <-> *
 *      In this situation we must change:
 *      B->left to y;
 *      A->right to x;
 *      x->left to A;
 *      y->right to B;
 *      y->left to x;
 *      x->right to y;
 *   * A <-> x <-> y <-> B <->... <-> *
 *   Special sub-case is now * <-> x <-> y <-> * but this then nothing must be done.
 *
 * 3) * A <-> y <-> B <-> x <-> C <-> *
 *      C->left = y;
 *      B->right = y;
 *      B->left = x;
 *      A->Right = x;
 *      x->right = B;
 *      x->left = A;
 *      y->left = B;
 *      y->right = C;
 *
 */

void FibMinPriorityQueue::Swap(FibonacciNode **x, FibonacciNode **y){
    FibonacciNode *_old_x_right = (*x)->Right, *_old_y_left = (*y)->Left;
    if((*x)->Right != *y){
        if((*y)->Right == *x ){
            // case 2)
            (*y)->Left->Right = *x;
            (*x)->Right->Left = *y;
            (*x)->Right = *y;
            (*y)->Left = *x;
        } else {
            // case 3)
            (*x)->Right->Left = *y;
            (*x)->Right = (*y)->Right;
            (*y)->Left->Right = *x;
            (*y)->Left = (*x)->Left;
            (*y)->Right->Left = *x;
            (*x)->Left->Right = *y;
        }
        // shared part of code
        (*y)->Right = _old_x_right;
        (*x)->Left = _old_y_left;
    } else if((*y)->Right != *x) { // exclude sub-case
        // case 1):
        (*x)->Left->Right = *y;
        (*y)->Right->Left = *x;
        (*x)->Right = (*y)->Right;
        (*y)->Left = (*x)->Left;
        (*x)->Left = *y;
        (*y)->Right = *x;
    }
    // actual swap
    FibonacciNode *pom = *x;
    *x = *y;
    *y = pom;
}

/*
 * Setters and getters start!
 */

int FibonacciNode::GetKey() {
    return Key;
}

void FibonacciNode::SetKet(int _key) {
    Key = _key;
}

int FibonacciNode::GetVrtIdx() {
    return VertexIdx;
}

void FibonacciNode::SetVrtIdx(int _idx) {
    VertexIdx = _idx;
}

/*
 * Setters and getters end!
 */

FibMinPriorityQueue::FibMinPriorityQueue() {
    Min = NULL;
    N = 0;
}

FibonacciNode::FibonacciNode(int _key) {
    Key = _key;
    Degree = 0;
    Parent = NULL;
    Child = NULL;
    Left = this;
    Right  = this;
    Mark = false;
}

bool FibMinPriorityQueue::Empty() {
    return Min == NULL;
}

void FibMinPriorityQueue::InsertToRootList(FibonacciNode *x) {
    x->Left = Min;
    x->Right = Min->Right;
    x->Right->Left = x;
    Min->Right = x;
}

FibonacciNode* FibMinPriorityQueue::Enqueue(int key, int _vert_idx) {
    FibonacciNode *x = new FibonacciNode(key);
    x->VertexIdx = _vert_idx;
    if(Min == NULL){
        Min = x;
        x->Left = x->Right = x;
    } else {
        InsertToRootList(x);
        if(x->Key < Min->Key) Min = x;
    }
    N++;
    return x;
}

FibonacciNode* FibMinPriorityQueue::Minimum() {
    return Min;
}

FibonacciNode* FibMinPriorityQueue::Dequeue() {
    FibonacciNode *z = Min;
    if(z != NULL){
        if(z->Child != NULL){
            FibonacciNode *x = z->Child;
            FibonacciNode *it = x;
            do {
                it->Parent = NULL;
                it = it->Right;
            } while(it->Right != x->Right);
            ConcatenateLists(Min, x);
        }
        DeleteFromRootList(z);
        if(z->Right == z) Min = NULL;
        else {
            Min = z->Right;
            Consolidate();
        }
        N--;
    }
    return z;
}

void FibMinPriorityQueue::Consolidate() {
    // Counting the golden ratio as a base of log
    const double g_ratio = (1 + sqrt(5.0)) / 2;
    double Size = log(N) / log (g_ratio);
    int S = static_cast<int>(ceil(Size)); // just in case -> in theory -> floor of that
    FibonacciNode **A = new FibonacciNode*[S];
    for(int i = 0; i < S; i++) A[i] = NULL;
    FibonacciNode *it = Min;
    FibonacciNode *Sentinel = it->Left;
    do {
        FibonacciNode *x = it;
        int d = x->Degree;
        while(d < S && A[d] != NULL && A[d] != x){
            FibonacciNode *y = A[d];
            if(x->Key > y->Key){
                it = y; // y stays on root list and x not - so that we must have it on the root list!
                Swap(&x, &y);
            }
            if(x != y){
                // prevents a Sentinel (only the ptr -> not a node that should disappear) to disappear from root list
                if(y == Sentinel) Sentinel = Sentinel->Right;
                Link(y, x);
                A[d] = NULL;
                d++;
            }
        }
        A[d] = x;
        it = it->Right;
    } while(it->Right != Sentinel->Right); // sentinel must be also processed (and we are sure that it doesn't disappear)
    Min = NULL;
    for(int i = 0; i < S; i++){
        if(A[i] != NULL){
            if(Min == NULL || A[i]->Key < Min->Key) Min = A[i];
        }
    }
    delete[] A;
}

void FibMinPriorityQueue::Link(FibonacciNode *y, FibonacciNode *x) {
    DeleteFromRootList(y);
    AddToChildList(x, y);
    y->Mark = false;
}

void FibMinPriorityQueue::DeleteFromRootList(FibonacciNode *y) {
    if(y->Right == y) return;
    // Do not break anything even if it's the last element on root list.
    y->Right->Left = y->Left;
    y->Left->Right = y->Right;
}

void FibMinPriorityQueue::AddToChildList(FibonacciNode *parent, FibonacciNode *new_child) {
    new_child->Parent = parent;
    if(parent->Child == NULL) {
        // We are adding first child...
        parent->Child = new_child;
        // Making 1-elem-doubly-linked-list
        new_child->Left = new_child->Right = new_child;
    } else {
        // Inserting between parent->Child and parent->Child->Right
        parent->Child->Right->Left = new_child;
        new_child->Right = parent->Child->Right;
        new_child->Left = parent->Child;
        parent->Child->Right = new_child;
    }
    parent->Degree++;
}

void FibMinPriorityQueue::DecreaseKey(FibonacciNode *elem, int new_key) {
    if(new_key > elem->Key) return; // Invalid operation!
    elem->Key = new_key;
    FibonacciNode *y = elem->Parent;
    // if Heap constrains are violated
    if(y != NULL && elem->Key < y->Key){
        Cut(elem, y);
        Cascading(y);
    }
    if(elem->Key < Min->Key) Min = elem;
}

void FibMinPriorityQueue::Cut(FibonacciNode *x, FibonacciNode *y) {
    DeleteFromChildList(y, x);
    InsertToRootList(x);
    x->Mark = false;
}

void FibMinPriorityQueue::DeleteFromChildList(FibonacciNode *parent, FibonacciNode *child) {
    parent->Degree--;
    child->Parent = NULL;
    if(child->Right == child) {
        // only one child!
        parent->Child = NULL;
        return;
    }
    // child->right exists for sure
    parent->Child = child->Right;
    child->Right->Left = child->Left;
    child->Left->Right = child->Right;
}

void FibMinPriorityQueue::Cascading(FibonacciNode *y) {
    FibonacciNode *z = y->Parent;
    if(z != NULL){
        if(!y->Mark) y->Mark = true;
        else {
            Cut(y, z);
            Cascading(z);
        }
    }
}

void FibMinPriorityQueue::DeleteKey(FibonacciNode *elem) {
    DecreaseKey(elem, INT_MIN);
    Dequeue();
}

/*
 * While concatenation we must virtually split both two lists
 * and be able to manage all four ends.
 * We have (after virtual split):
 *      L1_old_right <-> ... <-> L1
 *      L2 <-> ... <-> L2_old_right
 * Then we concatenate:
 *      L1->Right = L2;
 *      L2->Left = L1;
 *      L1_old_right <-> ... <-> L1 <-> L2 <-> ... <-> L2_old_right
 * And after:
 *      l1_old_right->Left = l2_old_left;
 *      l2_old_left->Right = l1_old_right;
 *      * <-> L1_old_right <-> ... <-> L1 <-> L2 <-> ... <-> L2_old_right <-> *
 */

void FibMinPriorityQueue::ConcatenateLists(FibonacciNode *L1, FibonacciNode *L2){
    if(L1 != NULL && L2 != NULL){ // List concatenation makes sense only if both are not empty
        FibonacciNode *l1_old_right = L1->Right, *l2_old_left = L2->Left;
        L1->Right = L2;
        L2->Left = L1;
        l1_old_right->Left = l2_old_left;
        l2_old_left->Right = l1_old_right;
    }
}

void FibMinPriorityQueue::DestructHeap(FibonacciNode *root, int lvl){
    if(root == NULL) return;
    root->Left->Right = NULL;
    while(root != NULL){
        FibonacciNode *it = root;
        root = root->Right;
        DestructHeap(it->Child, lvl + 1);
        delete it;
    }
    return;
}

FibMinPriorityQueue::~FibMinPriorityQueue() {
    DestructHeap(Min, 0);
}


