#include <iostream>
#include <assert.h>
#include "splay_bst.h"

void testSplay();

int main() {

	testSplay();
	return 0;
}

/*
Interface -
void insert(int key)
int remove(int key)
int get(int key)
*/
void testSplay() {

	BST tree;

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);

	assert(tree.get(1) == 1);
	assert(tree.get(2) == 2);
	assert(tree.get(3) == 3);

	assert(tree.remove(3) == 3);
	assert(tree.remove(2) == 2);
	assert(tree.remove(1) == 1);

	tree.insert(1);
	tree.insert(2);
	tree.insert(6);
	tree.insert(5);
	tree.insert(7);
	tree.insert(3);

    for(int i = 1; i <= 7; ++i) {
        if(i != 4)
            assert(tree.get(i) == i);
    }
}
