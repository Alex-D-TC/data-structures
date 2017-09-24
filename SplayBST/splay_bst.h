#ifndef SPLAY_BST_H
#define SPLAY_BST_H

class BST {

private:

	struct Node {
		int key;
		Node *left, *right;

		Node() : key{}, left{ nullptr }, right{ nullptr } {}
		Node(int nKey) : key{ nKey }, left{ nullptr }, right{ nullptr } {}
	};

	/* Integer comparison function
	Returns:
	0 if a = b
	1 if a > b
	-1 if a < b
	*/
	inline int compare(int a, int b) {
		int cmp = a < b ? -1 : 1;
		return a == b ? 0 : cmp;
	}

	// Single right rotation in BST
	Node* rotateRight(Node* node) {
		Node* left = node->left;
		node->left = left->right;
		left->right = node;
		node = left;
		return node;
	}

	// Single left rotation in BST
	Node* rotateLeft(Node* node) {
		Node* right = node->right;
		node->right = right->left;
		right->left = node;
		node = right;
		return node;
	}

	/*
	Brings a node which has the given key up to the root of the tree

	Fat children are a problem
	Fat children have potential
	We must promote the fat children
	--David Karger, MIT
	*/
	Node* splay(Node* node, int key) {

		if (node == nullptr)
			return nullptr;

		int cmp = compare(key, node->key);

		if (cmp < 0) { // Go left case

			// Our node is a leaf. We're done
			if (node->left == nullptr) {
				return node;
			}

			cmp = compare(key, node->left->key);

			if (cmp < 0) { // left-left case (zig-zig)
				node->left->left = splay(node->left->left, key);
				node = rotateRight(node);
			}
			else if (cmp > 0) { // left-right case (zig-zag)
				node->left->right = splay(node->left->right, key);

				if (node->left->right != nullptr)
					node->left = rotateLeft(node->left);
			}

			// A right rotate when the left node is null is nonsensical
			if (node->left == nullptr)
				return node;
			else
				return rotateRight(node);

		}
		else if (cmp > 0) { // Go right case

							// Our node is a leaf. We're done
			if (node->right == nullptr) {
				return node;
			}

			cmp = compare(key, node->right->key);

			if (cmp < 0) { // right-left case (zig-zag)
				node->right->left = splay(node->right->left, key);

				if (node->right->left != nullptr)
					node->right = rotateRight(node->right);
			}
			else if (cmp > 0) { // right-right case (zig-zig)
				node->right->right = splay(node->right->right, key);
				node = rotateLeft(node);
			}

			// A left rotate when the right node is null is nonsensical
			if (node->right == nullptr)
				return node;
			else
				return rotateLeft(node);
		}

		// We are right on the node
		return node;
	}

	Node* root;

	void destroy_bst(Node* node) {
		if (node == nullptr)
			return;

		destroy_bst(node->left);
		destroy_bst(node->right);

		delete node;
	}

public:

	BST() : root{ nullptr } {}
	~BST() { destroy_bst(root); }

	void insert(int key) {

		if (root == nullptr) {
			root = new Node(key);
			return;
		}

		Node* node = splay(root, key);
		int cmp = compare(key, node->key);

		if (cmp < 0) { // Splayed node is greater

			Node* newNode = new Node(key);
			newNode->right = node;
			newNode->left = node->left;
			node->left = nullptr;

			root = newNode;

		}
		else if (cmp > 0) { // Splayed node is smaller

			Node* newNode = new Node(key);
			newNode->left = node;
			newNode->right = node->right;
			node->right = nullptr;

			root = newNode;

		}
		else { // Overwrite value
			node->key = key;
			root = node;
		}

	}

	int remove(int key) {

		if (root == nullptr) {
			return -1;
		}

		root = splay(root, key);

		int cmp = compare(key, root->key);

		if (cmp == 0) {
			if (root->right == nullptr) {

				Node* top = root;

				root = root->left;
				int res = top->key;

				delete top;
				return res;
			}
			else {

				int res = root->key;
				Node* toRemove = root;

				Node* left = root->left;
				root = root->right;
				root = splay(root, key);
				root->left = left;

				delete toRemove;
				return res;
			}
		}

		return -1;
	}

	int get(int key) {

		if (root == nullptr) {
			return -1;
		}

		root = splay(root, key);

		return compare(key, root->key) == 0 ? root->key : -1;
	}

	int height(Node* node) {

		if (node == nullptr)
			return 0;

		int leftHeight = height(node->left),
			rightHeight = height(node->right);

		int height = 1;
		height += leftHeight > rightHeight ? leftHeight : rightHeight;

		return height;
	}

};


#endif
