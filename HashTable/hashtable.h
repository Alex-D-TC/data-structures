#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <random>
#include <string>
#include <chrono>

class HashTable {

private:

	struct Node {
		int key, value;

		Node() : key(EMPTY), value(EMPTY) {

		}

		Node(int nKey, int nValue) : key(nKey), value(nValue) {

		}
	};

	static const unsigned long long M31 = 2147483647;
	static const int DELETE_ME = NULL;
	static const int EMPTY = -1;
	static const unsigned int START_SIZE = 8;
	static const unsigned int WORD_SIZE = 32;

	long long seed =
		std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine engine;

	unsigned int binSpace = 3;
	unsigned int size, occupied;
	Node* array;


	/*
	Hashing formula:

	h(k) = ((a * k) mod 2^w) >> (w - r) where:

	w - the word size (32 in our case)
	r - binary space occupied by table size (aka table size is 2^r - 1)
	a - a random number
	- odd
	- 1 <= a <= 2^r - 1
	k - the key

	*/
	unsigned int hash(int key, unsigned int r) {

		long max = 1;
		max = max << r;

		key = key < 0 ? key * -1 : key;

		std::uniform_int_distribution<> dist(0, max);

		int a = dist(engine);

		unsigned long long powerSize = 1;
		powerSize = powerSize << WORD_SIZE;

		return ((static_cast<unsigned int>(a * key)) % (powerSize))
			>> (WORD_SIZE - r);

	}

	unsigned long long subHash(int key) {

		key = key < 0 ? key * -1 : key;
		unsigned long long hash = static_cast<unsigned long long>(key)
			% M31;

		// Handle edge case where hash = M31 - 1.
		if (hash == M31 - 1)
			return hash - 1;

		hash = (hash & 1) == 0 ? hash + 1 : hash;

		return hash;
	}

	/*
	Returns Mersenne 31. It has 10 letters.
	Something greater than 2 billion should be enough, really.
	-UNUSED-
	*/
	unsigned long long getMersennePrime() {
		unsigned long long m31 = 1;
		m31 = (m31 << 31) - 1;

		return m31;
	}

	unsigned int linearHash(int key, unsigned int r,
		unsigned int i) {
		return (hash(key, r) + i * subHash(key)) % size;
	}

	void changeSize(unsigned int newSize) {

		Node* tmpArray = new Node[size];
		for (unsigned int i = 0; i < size; ++i) {
			tmpArray[i] = array[i];
		}

		delete[] array;
		unsigned int tmpSize = size;

		if (newSize < size) {
			binSpace--;
		} else {
			binSpace++;
		}

		size = newSize;
		array = new Node[size];

		for (unsigned int i = 0; i < tmpSize; ++i) {
			if(tmpArray[i].key != EMPTY && tmpArray[i].key != DELETE_ME)
				this->add(tmpArray[i].key, tmpArray[i].value);
		}

		delete[] tmpArray;
	}

public:

	HashTable() :
		engine{ static_cast<unsigned int >(seed) },
		size(START_SIZE),
		occupied(0),
		array(new Node[size]) {

	}

	~HashTable() {
		delete[] array;
	}

	void add(int key, int value) {

		Node node(key, value);

		for (unsigned int i = 0; i < size; ++i) {
			unsigned int h = linearHash(key, binSpace, i);
			if (array[h].key == DELETE_ME || array[h].key == EMPTY) {
				array[h] = node;
				++occupied;
				break;
			}
		}

		if (occupied == size) {
			changeSize(size << 1);
		}
	}

	bool exists(int key) {

		for (unsigned int i = 0; i < size; ++i) {
			unsigned int h = linearHash(key, binSpace, i);
			if (array[h].key == key) {
				return true;
			}
		}

		return false;
	}

	int get(int key) {

		for (unsigned int i = 0; i < size; ++i) {
			unsigned int h = linearHash(key, binSpace, i);
			if (array[h].key == EMPTY) {
				break;
			}
			if (array[h].key == key) {
				return array[h].value;
			}
		}

		return EMPTY;
	}

	int remove(int key) {

		int value = EMPTY;

		for (unsigned int i = 0; value == EMPTY && i < size; ++i) {
			unsigned int h = linearHash(key, binSpace, i);
			if (array[h].key == EMPTY) {
				return EMPTY;
			}
			if (array[h].key == key) {
				value = array[h].value;
				array[h].key = DELETE_ME;
				--occupied;
			}
		}

		if (occupied < size / 4) {
			changeSize(size >> 1);
		}

		return value;
	}

};

#endif
