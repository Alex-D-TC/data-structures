#include <iostream>
#include <assert.h>
#include "heap.h"


void testMaxHeap();

int main() {

    testMaxHeap();

    return 0;
}

void testMaxHeap() {

    Heap h;

    assert(h.is_empty());

    h.insert(10);
    h.insert(12);
    h.insert(2);
    h.insert(4);
    h.insert(18);
    h.insert(6);

    assert(!h.is_empty());
    assert(h.get_size() == 6);
    assert(h.get_max() == 18);
    assert(h.extract_max() == 18);
    assert(h.get_size() == 5);
    assert(h.get_max() == 12);


}

