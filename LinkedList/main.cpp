#include <iostream>
#include "linkedList.h"
#include <assert.h>

void runTests();

int main() {

	runTests();
	return 0;
}

void runTests() {

	LinkedList list;

	assert(list.size() == 0);
	assert(list.empty() == true);

	list.push_front(3);
	list.push_front(2);
	list.push_front(1);
	list.push_front(0);

	// LIST COMPOSITION: 0 1 2 3

	assert(list.size() == 4);
	assert(list.empty() == false);
	assert(list.front() == 0);
	assert(list.back() == 3);

	assert(list.value_at(3) == 3);
	assert(list.value_at(1) == 1);


	assert(list.pop_front() == 0);
	assert(list.pop_back() == 3);
	assert(list.size() == 2);

	// LIST COMPOSITION 1 2
	list.insert(2, 3);

	// LIST COMPOSITION 1 2 3
	assert(list.value_at(2) == 3);
	assert(list.back() == 3);
	assert(list.value_n_from_end(0) == 3);
	assert(list.value_n_from_end(2) == 1);

	list.reverse();

	// LIST COMPOSITION 3 2 1
	assert(list.front() == 3);
	assert(list.back() == 1);
	assert(list.value_n_from_end(0) == 1);
	assert(list.value_n_from_end(2) == 3);

	assert(list.remove_value(3) == 3);
	assert(list.size() == 2);

	// LIST COMPOSITION 2 1

	assert(list.remove_value(4) == -1);
	assert(list.size() == 2);
	
	assert(list.remove_value(2) == 2);
	
	// LIST COMPOSITION 1
	
	assert(list.size() == 1);
	assert(list.front() == 1);
	assert(list.back() == 1);

	list.push_back(3);

	// LIST COMPOSITION 1 3

	assert(list.size() == 2);
	assert(list.front() == 1);
	assert(list.back() == 3);
	
	list.remove_value(3);

	// LIST COMPOSITION 1

	assert(list.size() == 1);
	assert(list.front() == 1);
	assert(list.size() == 1);
}
