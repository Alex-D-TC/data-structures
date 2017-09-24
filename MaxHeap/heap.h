#ifndef HEAP_H
#define HEAP_H

class Heap {

private:

    unsigned int size;
    int* array;
    unsigned int occupied;

    static void sift_up(int* array, unsigned int index) {
        unsigned int p = index;
        while(p != 0 && array[p / 2] < array[p]) {
            int aux = array[p / 2];
            array[p / 2] = array[p];
            array[p] = aux;
            p /= 2;
        }
    }

    static void sift_down(int* array, unsigned int occupied, unsigned int index) {
        unsigned int p = index, next = occupied + 1;
        
        while(p != next) {
            
            next = p;
            int max = array[p];

            if(2 * p < occupied && max < array[2 * p]) {
                max = array[2 * p];
                next = 2 * p;
            } else if(2 * p + 1 < occupied && max < array[2 * p + 1]) {
                max = array[2 * p + 1];
                next = 2 * p + 1;
            }
        
            int aux = array[p];
            array[p] = array[next];
            array[next] = aux;
            p = next;
        }
    }

public:

    Heap() : size(10), array(new int[size]), occupied(0) {                
    }

    Heap(unsigned int s) : size(s), array(new int[size]), occupied(0) {
    }

    ~Heap() {
        delete[] array;
    }

    void insert(int elem) {

        if(occupied == size) {
            return; // Full... sorry
        }

        array[++occupied] = elem;
        sift_up(array, occupied - 1);
    }

    unsigned int get_size() {
        return occupied;
    }

    int get_max() {
        return array[0];
    }

    bool is_empty() {
        return occupied == 0;
    }

    int extract_max() {
        int max = array[0];
        array[0] = array[--occupied];
        sift_down(array, occupied, 0);

        return max;
    }

    static int* heapify(int* arr, unsigned int size) {
        
        for(unsigned int i = size / 2; i >= 1; --i) {
            sift_down(arr, size, i);
        }

        return arr;
    }

    static int* heap_sort(int* arr, unsigned int size) {
        size++;
        return arr;
    }

    int remove(unsigned int index) {
        if(index >= occupied) {
            return -1;
        }
        int num = array[index];
        array[index] = array[--occupied];
        sift_down(array, occupied, index);
        return num;
    }

};

#endif
