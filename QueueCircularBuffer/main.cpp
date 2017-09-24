#include "queue.h"
#include <assert.h>

void runTests();

int main() {

    runTests();

    return 0;
}

void runTests() {
    Queue q(20);

    assert(q.empty() == true);
    assert(q.full() != true);

    // QUEUE COMPL 1 2 3 4 5 6 7 8

    for(int i = 0; i < 10; ++i) {
        q.enqueue(i);
    }

    assert(q.empty() == false);

    assert(q.dequeue() == 0);
    assert(q.dequeue() == 1);
    assert(q.dequeue() == 2);
    assert(q.dequeue() == 3);
    assert(q.dequeue() == 4);
    assert(q.dequeue() == 5);
    assert(q.dequeue() == 6);
    assert(q.dequeue() == 7);
    assert(q.dequeue() == 8);
    assert(q.dequeue() == 9);
    assert(q.dequeue() == -1);
    assert(q.dequeue() == -1);

    assert(q.empty());

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
