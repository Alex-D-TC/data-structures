#ifndef QUEUE_H
#define QUEUE_H

#include <string>

class Queue {

private:

    const static unsigned long long STD_SIZE = 10;
    
    unsigned long long size;
    int* array;
    int readIndex = 0, writeIndex = 0;

    int incrementIndex(int index) {
        return (static_cast<unsigned long long>(index) == size - 1)? 
                0 : index + 1;
    }

    void clearBuffer() {
        std::memset(array, -1, sizeof(int) * size);
    }

public:

    Queue(): size(STD_SIZE), array(new int[STD_SIZE]) {
        clearBuffer();
    }

    Queue(unsigned long long nSize): size(nSize), array(new int[nSize]) {
        clearBuffer();
    }

    ~Queue() {
        delete[] array;
    }

    void enqueue(int num) {

        if(full()) {
            return;
        }

        array[writeIndex] = num;
        writeIndex = incrementIndex(writeIndex);
    }

    int dequeue() {

        if(empty()) {
            return -1;
        }
   
        int val = array[readIndex];
        array[readIndex] = -1;
        readIndex = incrementIndex(readIndex);

        return val;
    }

    bool empty() {
        return readIndex == writeIndex;
    }

    bool full() {
        return array[incrementIndex(readIndex)] != -1 &&
               array[incrementIndex(writeIndex)] != -1;
    }

};

#endif
