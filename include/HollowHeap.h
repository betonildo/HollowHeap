#include <stdlib.h>
#include <math.h>

#ifndef HOLLOWHEAP_H
#define HOLLOWHEAP_H

#include "definitions.h"

typedef struct Item Item;
typedef struct Node Node;

struct Node {
    Item* item;
    U32 key;
    Node* firstChild;
    Node* nextSibling;
    U32 rank;
    U32 N;
};

struct Item {
    Node* node;
    U32 vertice;
};

#ifdef __cplusplus
extern "C" {
#endif

    Item* make_element(U32 vertice);
    Node* make_heap(Item* e, U32 key); //O(1)
    Item* findmin(Node* h); // O(1)
    Node* getmin(Node* h); //O(1)
    Node* insert(Item* e, U32 key, Node* h); //O(1)
    Node* decrease_key(Item* e, U32 key, Node* h); //O(1)
    Node* delete_element(Item* e, Node* h); // log(N)
    Node* delete_min(Node* h); // log(N)
    Node* meld(Node* h1, Node* h2); //O(1)
    U32 link_heap(Node* h, Node** R); // log(N)
    Node* link(Node* t1, Node* t2); //O(1)
    Node* makechild(Node* w, Node* l); //O(1)

#ifdef __cplusplus
};
#endif

    
// template <class ElementType>
// class HollowHeap {
    
// public:


//     void insert(ElementType e, U32 key);
//     void decreaseKey(ElementType e, U32 key);
    

// };

#endif /*HOLLOWHEAP_H*/