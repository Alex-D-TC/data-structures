#include "queue.h"
#include "../LinkedList/linkedList.h"
#include <iostream>
#include <assert.h>

void runTests();

int main() {

    runTests();
    return 0;
}

void runTests() {

    Queue q;

    assert(q.empty() == true);

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    // QUEUE COMP : 1 2 3

    assert(q.dequeue() == 1);
    assert(q.dequeue() == 2);
    assert(q.dequeue() == 3);

    // QUEUE COMP : 1 2 3

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    assert(q.dequeue() == 1);
    q.enqueue(4);
    assert(q.dequeue() == 2);
    assert(q.dequeue() == 3);
    assert(q.empty() == false);
    assert(q.dequeue() == 4);
    assert(q.empty() == true);
}
