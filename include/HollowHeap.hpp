#ifndef HOLLOWHEAP_HPP
#define HOLLOWHEAP_HPP

#include "definitions.h"

template <class ElementType>
class HollowHeap {
    
private:
    struct Node {
        Item* item;
        U32 key;
        Node* firstChild;
        Node* nextSibling;
        U32 rank;
    };

    struct Item {
        Node* node;
        ElementType e;
    };



public:


    void insert(ElementType e, U32 key);
    void decreaseKey(ElementType e, U32 key);
    /*
    Item* make_element();
    Node* make_heap(Item* e, U32 key); //O(1)
    Item* findmin(Node* h); // O(1)
    Node* getmin(Node* h); //O(1)
    Node* insert(Item* e, U32 key, Node* h); //O(1)
    Node* decrease_key(Item* e, U32 key, Node* h); //O(1)
    Node* delete_element(Item* e, Node* h); // log(N)
    Node* delete_min(Node* h); // log(N)
    Node* meld(Node* h1, Node* h2); //O(1)
    void link_heap(Node* h, Node** R); // log(N)
    Node* link(Node* t1, Node* t2); //O(1)
    Node* makechild(Node* w, Node* l); //O(1)
    */

};

#endif /*HOLLOWHEAP_HPP*/