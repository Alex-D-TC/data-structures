#ifndef QUEUE_H
#define QUEUE_H

#include "../LinkedList/linkedList.h"

class Queue {

private:

    LinkedList list;

public:

    void enqueue(int value) {
        list.push_back(value);
    }

    int dequeue() {
        return list.pop_front();
    }

    bool empty() {
        return list.empty();
    }

};

#endif
