#include "Item.h"

#ifndef NODE_H
#define NODE_H

typedef struct {
    Item* item;
    U32 key;
    Node* firstChild;
    Node* nextSibling;
    U32 rank;
    U32 N;
} Node;

#endif /*NODE_H*/