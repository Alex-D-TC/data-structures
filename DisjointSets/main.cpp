#include <iostream>
#include <vector>
#include <assert.h>
#include "disjoint_set.h"

void testSet();
void testCharSets();

int main() {
    testSet();
    testCharSets();
}

void testSet() {

    std::vector<int> nums = {0,1,2,3,4,5,6,7};

    DisjointSet<int> s{nums.data(), static_cast<int>(nums.size())};

    for(int i = 0; i < 8; ++i) {
        assert(s.find(i) == i);
    }

    s.join(0, 1);
    assert(s.find(1) == s.find(0));

    s.join(1, 2);
    assert(s.find(1) == s.find(2));
    assert(s.find(0) == s.find(2));

    s.join(3, 4);
    assert(s.find(3) == s.find(4));

    assert(s.find(5) == 5);

    s.join(6, 7);
    assert(s.find(6) == s.find(7));
} 

void testCharSets() {

    char array[]  = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'U'};

    DisjointSet<char> s{array, 8};

    for(int i = 0; i < 8; ++i) {
        assert(s.find(array[i]) == array[i]);
    }

    s.join('A', 'B');
    assert(s.find('B') == s.find('A'));

    s.join('B', 'C');
    assert(s.find('B') == s.find('C'));
    assert(s.find('A') == s.find('C'));

    s.join('D', 'E');
    assert(s.find('D') == s.find('E'));

    assert(s.find('F') == 'F');

    s.join('G', 'U');
    assert(s.find('G') == s.find('U'));
}
