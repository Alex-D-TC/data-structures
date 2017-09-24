#pragma once


class LinkedList {

private:

	struct Node {
		int _value;
		Node* _next;
		int _size;

		Node() : _value(0), _next(nullptr), _size(0) {
		}

		Node(int value, Node* next) : _value(value), _next(next), _size(0) {
		}
	};

	Node *_front, *_back;

public:

	LinkedList() : _front(nullptr), _back(nullptr) {

	}

	int size() {

		if (_front == nullptr) {
			return 0;
		}

		return _front->_size + 1;
	}

	bool empty() {
		return _front == nullptr;
	}

	int value_at(int index) {
		if (index > _front->_size) {
			return -1;
		}

		Node* p;
		for (p = _front; index > 0; index--, p = p->_next);

		return p->_value;
	}

	void push_front(int value) {
		Node* node = new Node();

		
		node->_value = value;
		node->_next = _front;
		node->_size = _front == nullptr ? 0 : _front->_size + 1;

		if (_back == nullptr) {
			_back = node;
		}

		_front = node;
	}

	int pop_front() {

		if (_front == nullptr) {
			return -1;
		}

		Node* node = _front;

		int value = node->_value;
		_front = _front->_next;

		delete node;
		return value;
	}

	void push_back(int value) {

		if (_front == nullptr) {
			// Empty list case
			Node* node = new Node(value, nullptr);

			_front = node;
			_back = node;

			return;
		}

		for (Node* p = _front; p->_next != nullptr; p = p->_next) {
			++p->_size;
		}

		Node* node = new Node();
		_back->_size++;
		_back->_next = node;
		node->_value = value;
		
		_back = node;
	}

	int pop_back() {

		if (_back == nullptr) {
			return -1;
		}

		Node* node;
		for (node = _front;
		node->_next->_next != nullptr;
			node = node->_next) {

			--node->_size;
		}

		if (node->_next == _back) {
			_back = node;
		}

		int value = node->_next->_value;
		node->_next = nullptr;
		node->_size--;

		delete node->_next;
		return value;
	}

	int front() {
		return _front == nullptr ? -1 : _front->_value;
	}

	int back() {
		return _back == nullptr ? -1 : _back->_value;
	}

	void insert(int index, int value) {
		
		if (index == 0) {
			Node* newNode = new Node();
			newNode->_next = _front;
			newNode->_value = value;
			newNode->_size = _front->_size + 1;
			_front = newNode;
			return;
		}

		if (index == _front->_size + 1) {
			Node* newNode = new Node();
			_back->_next = newNode;
			_back->_size++;
			newNode->_value = value;

			for (Node* node = _front; node != _back; node = node->_next) {
				node->_size++;
			}

			_back = newNode;
			return;
		}

		if (index > _front->_size) {
			return;
		}

		Node* node;
		for (node = _front; index > 1; --index, node = node->_next) {
			node->_size++;
		}

		Node* newNode = new Node();
		newNode->_value = value;
		newNode->_next = node->_next->_next;
		newNode->_size = node->_size + 1;

		node->_next = newNode;
	}

	int erase(int index) {
		Node* node = _front;

		if (index > node->_size) {
			return -1;
		}

		for (; index > 1; --index, node = node->_next);

		int value = node->_next->_value;

		if (node->_next == _back) {
			// We are removing the back pointer
			_back = node;
		}

		node->_next = node->_next->_next;

		return value;
	}

	int value_n_from_end(int n) {

		// Invalid index
		if (n > _front->_size) {
			return -1;
		}

		Node* node = _front;
		for (; n != node->_size; node = node->_next);

		return node->_value;
	}

	void reverse() {

		LinkedList l;

		for (Node* node = _front; node != nullptr; node = node->_next) {
			l.push_front(node->_value);
		}

		_front = l._front;
		_back = l._back;
	}

	int remove_value(int value) {

		// Check front has that value
		if (_front->_value == value) {
			int val = _front->_value;
			_front = _front->_next;
			return val;
		}


		// First round is the value search
		Node* node;
		for (node = _front;
			node->_next != nullptr && node->_next->_value != value;
			node = node->_next);

		if (node->_next == nullptr && node->_value != value) {
			return -1;
		}

		// On the next we update the sizes
		for (node = _front;
			node->_next != nullptr && node->_next->_value != value;
			node = node->_next) {

			--node->_size;
		}


		--node->_size;

		// Check if we want to remove back
		if (node->_next == _back) {
			_back = node;
		}


		int val = node->_next->_value;
		node->_next = node->_next->_next;

		return val;
	}

};

