#include "definitions.h"

#ifndef HOLLOWHEAP_H
#define HOLLOWHEAP_H


struct Item {
    Node* node;
};

struct Node {
    Item* item;
    U32 key;
    Node* firstChild;
    Node* nextSibling;
    U32 rank;
};
    
template <class ElementType>
class HollowHeap {
    
public:
    void insert(ElementType e, U32 key);
    void decreaseKey(ElementType e, U32 key);
    
};

#endif /*HOLLOWHEAP_H*/