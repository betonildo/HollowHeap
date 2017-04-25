#include "HollowHeap.h"

#ifdef __cplusplus
extern "C" {
#endif

    Item* make_element() {
        return (Item*)malloc(sizeof(Item));
    }

    Node* make_heap(Item* e, U32 key) {
        Node* n = (Node*) malloc(sizeof(Node));
        n->item = e;
        n->key = key;
        n->firstChild = NULL;
        n->nextSibling = NULL;
        n->rank = 0;
        n->N = 0; // metadata for delete-min con
        return n;
    }

    Item* findmin(Node* h) {
        return h != NULL ? h->item : NULL;
    }

    Node* getmin(Node* h) {
        return h;
    }

    Node* insert(Item* e, U32 key, Node* h) {
        Node* rh = meld(make_heap(e, key), h);
        rh->N += 1;
        return rh;
    }

    Node* decrease_key(Item* e, U32 key, Node* h) {
        Node* u = e->node;
        Node* v = make_heap(e, key);
        v->rank = MAX(0, u ? u->rank - 2 : 0);

        if (u && u->rank >= 2) {
            v->firstChild = u->firstChild->nextSibling->nextSibling;
            u->firstChild->nextSibling->nextSibling = NULL;
        }

        Node* rh = meld(v, h);
        rh->N += 1;
        return rh;
    }

    Node* delete_element(Item* e, Node* h) {
        free(e->node->item);
        e->node->item = NULL;
        if (e->node == h)
            return delete_min(h);
        return h;
    }

    Node* delete_min(Node* h) {
        if (h == NULL) return NULL;
        free(h->item);
        h->item = NULL;

        // defining M is into colorary definition
        // TODO:    to reduce the number N, used to discover M, each hollowNode that is
        //          removed from heap, decrements one
        U32 M = ceil(logBase(h->N, PHI));

        Node** R = (Node**) malloc(sizeof(Node*) * M);

        Node* r = h;
        do {
            Node* rn = r->nextSibling;
            link_heap(r, R);
            r = rn;
        }
        while(r != h);

        h = NULL;

        for (U32 i = 0; i < M; i++) {
            if (R[i] != NULL) {
                R[i]->nextSibling = R[i];
                h = meld(h, R[i]);
            }
        }

        return h;
    }

    Node* meld(Node* h1, Node* h2) {
        if (h1 == NULL) return h2;
        if (h2 == NULL) return h1;

        // SWAP
        Node* tmp = h2->nextSibling;
        h2->nextSibling = h1->nextSibling;
        h1->nextSibling = tmp;

        if (h1->key <= h2->key) return h1;
        else return h2;
    }

    void link_heap(Node* h, Node** R) {
        // h is hollow
        if (h->item == NULL) {
            Node* r = h->firstChild;
            while (r != NULL) {
                Node* rn = r->nextSibling;
                link_heap(r, R);
                r = rn;
            }
            free(h);
            h = NULL;
        }
        else {
            U32 i = h->rank;
            while (R[i] != NULL) {
                h = link(h, R[i]);
                R[i] = NULL;
                i = i + 1;
            }
            R[i] = h;
        }
    }

    Node* link(Node* t1, Node* t2) {
        if (t1->key <= t2->key)
            return makechild(t1, t2);
        else
            return makechild(t2, t1);
    }

    Node* makechild(Node* w, Node* l) {
        l->nextSibling = w->firstChild;
        w->firstChild = l;
        w->rank = w->rank + 1;
        return w;
    }
#ifdef __cplusplus
};
#endif