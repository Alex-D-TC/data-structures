#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <vector>

template <class T>
class DisjointSet {

private:

    T* values;
    int* parent;
    int size;

    inline int locateElement(T element) {
        for(int i = 0; i < size; ++i)
            if(values[i] == element)
                return i;
        return -1;
    }

    inline void copyValues(T* vals) {
        
        values = new T[static_cast<unsigned long long>(size)];

        for(int i = 0; i < size; ++i)
            values[i] = vals[i];
    }

    inline void initParents() {
        
        parent = new int[static_cast<unsigned long long>(size)];
        
        for(int i = 0; i < size; ++i)
            parent[i] = i;
    }

    int findParent(int value) {
        return parent[value] == value? value : (parent[value] = findParent(parent[value])); 
    }

public:

    DisjointSet(T* _values, int _size)
    : size{_size} {
        copyValues(_values);
        initParents();    
    }

    ~DisjointSet() {
        delete[] parent;
        delete[] values;
    }

    T find(T value) {

        int index = locateElement(value);

        assert(index >= 0);

        return values[findParent(index)];
    }

    void join(T first, T second) {

        int indexA = locateElement(first),
            indexB = locateElement(second);

        if(indexA < 0 || indexB < 0)
            return;

        int rootA = findParent(indexA),
            rootB = findParent(indexB);

        parent[rootB] = rootA;
    }

};

#endif
