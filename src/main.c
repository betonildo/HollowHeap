#include <stdio.h>
#include "HollowHeap.h"

int main() {

    Item* e = make_element();

    Node* h = make_heap(e, 123);

    h = insert(make_element(), 314, h);

    Item* el = findmin(h);
    h = decrease_key(el, 314, h);

    // double _8_2 = logBase(8, 2);
    // printf("%f\n", _8_2);

    return 0;
}