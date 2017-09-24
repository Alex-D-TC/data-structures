#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <vector>
#include <algorithm>
#include <iterator>

class RedBlackTree {

private:

	enum Color {
		RED, BLACK
	};

	struct Node {
		int key;
		Node *parent, *left, *right;
		Color c;

		Node(int _key)
			: key{ _key }, parent{ nullptr }, left{ nullptr }, right{ nullptr }, c{ RED } {}

		Node(int _key, Node* _pred)
			: key{ _key }, parent{ _pred }, left{ nullptr }, right{ nullptr }, c{ RED } {}
	};

	Node* root;

	void deleteTree(Node* node) {

		if (node == nullptr)
			return;

		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}

	Color getColor(Node* node) {
		return node == nullptr ? BLACK : node->c;
	}

	Node* getUncle(Node* node) {
		Node* grandfather = node->parent->parent;

		return grandfather->left == node->parent ?
			grandfather->right : grandfather->left;
	}

	void insert_rec(Node* node, int key) {

		if (node->key > key) {
			if (node->left == nullptr) {

				Node* newNode = new Node(key, node);
				node->left = newNode;
				Node* oldParent = node->parent;
				insert_rebalance(newNode);

				// We have rotated the root
				if (node->parent == nullptr && root == oldParent) {
					root = node;

					// Clear parent. For cleanness
					root->parent = nullptr;
				}
			}
			else {
				insert_rec(node->left, key);
			}
		}
		else if (node->key < key) {
			if (node->right == nullptr) {

				Node* newNode = new Node(key, node);
				node->right = newNode;
				Node* oldParent = node->parent;
				insert_rebalance(newNode);

				// We have rotated the root.
				if (node->parent == nullptr &&  root == oldParent) {
					root = node;
					// Clear parent. For cleanness
					root->parent = nullptr;
				}
			}
			else {
				insert_rec(node->right, key);
			}
		}

	}

	void rotateLeft(Node* node) {
		node->right->parent = node->parent;
		node->parent = node->right;

		Node* right = node->right;

		node->right = node->right->left;
		right->left = node;

		if (right->parent != nullptr) {
			if (right->parent->left == right->left)
				right->parent->left = right;
			else
				right->parent->right = right;
		}
	}

	void rotateRight(Node* node) {
		node->left->parent = node->parent;
		node->parent = node->left;

		Node* left = node->left;

		node->left = node->left->right;
		left->right = node;

		if (left->parent != nullptr) {
			if (left->parent->left == left->right)
				left->parent->left = left;
			else
				left->parent->right = left;
		}
	}

	void insert_rebalance(Node* node) {

		// If we hit the root, color it from red to black
		if (node->parent == nullptr) {
			node->c = BLACK;
			return;
		}

		// Do nothing if the parent is BLACK
		if (node->parent->c == BLACK) {
			return;
		}

		// Resolve trivial case where we only have two nodes
		if (node->parent->parent == nullptr) {
			node->parent->c = BLACK;
			return;
		}

		/*
		The inserted node is implicitly red.
		We know the parent must be red, since we inserted in a black node.
		The grandparent must be black, since it has a red child.
		Therefore, all further cases depend on the uncle and its position
		relative to the inserted node
		*/

		Node* uncle = getUncle(node);

		/*
		Case 1. The uncle is red.
		Trivial, we change both children of the grandparent to black
		*/
		if (getColor(uncle) == RED) {
			uncle->c = BLACK;
			node->parent->c = BLACK;
			node->parent->parent->c = RED;
			insert_rebalance(node->parent->parent);
		}

		/*
		Left - Left case.
		Rotate-right the parent. Recolor.
		*/
		else if (node->parent->left == node && node->parent->parent->right == uncle) {
			node->parent->c = BLACK;
			node->parent->parent->c = RED;
			rotateRight(node->parent->parent);
		}

		/*
		Right - Right case.
		Rotate-left the parent. Recolor.
		*/
		else if (node->parent->right == node && node->parent->parent->left == uncle) {
			node->parent->c = BLACK;
			node->parent->parent->c = RED;
			rotateLeft(node->parent->parent);
		}

		/*
		Left - Right case.
		Rotate-left the parent, then Rotate-right the node. Recolor.
		*/
		else if (node->parent->right == node && node->parent->parent->right == uncle) {
			node->parent->parent->c = RED;
			node->c = BLACK;
			rotateLeft(node->parent);
			rotateRight(node->parent);
		}

		/*
		Right - Left case.
		Rotate-right the parent, then Rotate-left the node. Recolor.
		*/
		else if (node->parent->left == node && node->parent->parent->left == uncle) {
			node->parent->parent->c = RED;
			node->c = BLACK;
			rotateRight(node->parent);
			rotateLeft(node->parent);
		}

	}


	// Debug function
	std::vector<int> inorder_transversal(Node* node) {

		if (node == nullptr) {
			return std::vector<int>{};
		}

		std::vector<int> leftVector = inorder_transversal(node->left);
		leftVector.push_back(node->key);
		std::vector<int> rightVector = inorder_transversal(node->right);
		std::copy(rightVector.begin(),
			rightVector.end(),
			std::back_inserter(leftVector));
		return leftVector;
	}

public:

	RedBlackTree() : root{ nullptr } {}

	~RedBlackTree() {
		deleteTree(root);
	}

	int get(int key) {
		return key++;
	}

	void insert(int key) {
		if (root == nullptr) {
			root = new Node(key);
			return;
		}
		insert_rec(root, key);
	}

	int remove(int key) {
		return key++;
	}


	// Test function
	std::vector<int> transversal() {
		return inorder_transversal(root);
	}

};

#endif
