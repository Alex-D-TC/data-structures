#include <iostream>
#include "red_black_tree.h"
#include <assert.h>
#include <vector>
#include <algorithm>

std::vector<int> inorderT(RedBlackTree tree);
void run();

int main() {
	run();
	return 0;
}

void run() {
	RedBlackTree tree;

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(5);
	tree.insert(4);

    std::vector<int> transversal = tree.transversal();

    std::for_each(transversal.begin(), transversal.end(), 
                    [](int num) {
                        std::cout << num << " ";
                    });
    std::cout << std::endl;
}
