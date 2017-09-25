// PATRICIA_TREE.cpp : Defines the entry point for the console application.
//

#include "PatriciaTree.h"
#include <assert.h>
#include <random>
#include <vector>

void treeTests() {

	PatriciaTree tree{};

	assert(!tree.lookup("caca"));

	tree.insert("cac");

	assert(tree.lookup("cac"));

	assert(!tree.lookup("caca"));

	tree.insert("caca");

	assert(tree.lookup("caca"));

	assert(tree.lookup("cac"));

	tree = PatriciaTree{};

	tree.insert("caca");

	tree.insert("cac");

	assert(tree.lookup("caca"));

	assert(tree.lookup("cac"));

	tree = PatriciaTree{};

	tree.insert("caca");

	tree.insert("caco");

	assert(tree.lookup("caca"));

	assert(tree.lookup("caco"));

	tree = PatriciaTree{};

	tree.insert("ca");

	tree.insert("co");

	tree.insert("cacofonie");

	assert(tree.lookup("ca"));

	assert(tree.lookup("co"));

	assert(tree.lookup("cacofonie"));

	assert(!tree.lookup("caco"));
}

int main()
{
	treeTests();
    return 0;
}
