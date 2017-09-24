#include <iostream>
#include <assert.h>
#include "bst.h"

void testBST();

int main() {

	testBST();
	return 0;
}

void testBST() {

	BST tree;

	assert(tree.is_binary_search_tree());

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);

	tree.print_values();
	std::cout << std::endl;

	assert(tree.get_node_count() == 3);
	assert(tree.get_height() == 3);

	assert(tree.delete_value(3) == 3);
	assert(tree.get_node_count() == 2);
	assert(tree.get_height() == 2);

	assert(tree.delete_value(2) == 2);
	assert(tree.get_node_count() == 1);
	assert(tree.get_height() == 1);

	assert(tree.delete_value(1) == 1);
	assert(tree.get_node_count() == 0);
	assert(tree.get_height() == 0);

	tree.print_values();
	std::cout << std::endl;

	tree.insert(10);
	tree.insert(3);
	tree.insert(6);
	tree.insert(8);
	tree.insert(4);
	tree.insert(12);
	tree.insert(11);
	tree.insert(13);

	tree.print_values();
	std::cout << std::endl;

	assert(tree.get_height() == 4);
	assert(tree.get_node_count() == 8);

	tree.delete_value(3);
	assert(tree.get_height() == 3);
	assert(tree.get_node_count() == 7);

	tree.delete_value(13);
	assert(tree.get_height() == 3);
	assert(tree.get_node_count() == 6);

	tree.delete_value(6);
	assert(tree.get_height() == 3);
	assert(tree.get_node_count() == 5);

	assert(tree.get_min() == 4);
	assert(tree.get_max() == 12);

	assert(tree.get_successor(11) == 12);
	assert(tree.get_successor(10) == 11);
	assert(tree.get_successor(8) == 10);
	assert(tree.get_successor(4) == 8);

	tree.print_values();
	std::cout << std::endl;

	assert(tree.is_binary_search_tree());

	assert(tree.is_in_tree(11));
	assert(!tree.is_in_tree(0));

}

