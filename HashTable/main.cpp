#include <iostream>
#include "hashtable.h"
#include <assert.h>

void testHashTable();

int main() {

	testHashTable();

	return 0;
}

void testHashTable() {

	HashTable table;

	table.add(13, 44);
	table.add(14, 45);
	table.add(15, 46);

	// TABLE FORMAT: (13, 44), (14, 45), (15, 46)

	assert(!table.exists(12));
	assert(table.exists(13));
	assert(table.exists(14));
	assert(table.exists(15));
	assert(table.get(14) == 45);
	assert(table.get(13) == 44);
	assert(table.get(15) == 46);
	assert(table.remove(14) == 45);

	// TABLE FORMAT : (13, 44), (15, 46)

	assert(!table.exists(14));
	assert(table.get(14) == -1);

	table.remove(13);
	table.remove(15);

	// TABLE EMPTY

	for (int i = 1; i <= 10; ++i) {
		table.add(i, 40 + i);
	}

	/* TABLE FORMAT :

	(1, 41)
	(2, 42)
	(3, 43)
	(4, 44)
	(5, 45)
	(6, 46)
	(7, 47)
	(8, 48)
	(9, 49)
	(10, 50)

	*/

	for (int i = 1; i <= 10; ++i) {
		assert(table.get(i) == 40 + i);
	}

	for (int i = 1; i <= 6; ++i) {
		assert(table.remove(i) == 40 + i);
	}

	/* TABLE FORMAT :

	(7, 47)
	(8, 48)
	(9, 49)
	(10, 50)

	*/

	for (int i = 7; i <= 10; ++i) {
		assert(table.remove(i) == 40 + i);
	}

	// TABLE IS EMPTY
}
