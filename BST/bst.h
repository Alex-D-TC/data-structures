#ifndef BST_H
#define BST_H

class BST {

private:

	/*
	count - The number of nodes in this binary search tree
	height - The size of this binary search tree
	*/
	struct Node {
		int val, count, height;
		Node *left, *right;

		Node() : val(0), count(1), height(1), left(nullptr), right(nullptr) {}

		Node(int v) : val(v), count(1), height(1), left(nullptr), right(nullptr) {}

	};

	Node* root;

	void updateHeight(Node* node) {

		Node *left = node->left,
			*right = node->right;

		//  Just in case updateHeight gets used in the context of a leaf
		// ...for some reason
		if (left == nullptr && right == nullptr) {
			node->height = 1;
			return;
		}

		int maxH;
		if (left != nullptr && right != nullptr) {
			maxH = left->height > right->height ? left->height : right->height;
		}
		else {
			maxH = left != nullptr ? left->height : right->height;
		}

		node->height = maxH + 1;
	}

	void insert_rec(Node* node, int value) {

		if (node->val == value)
			return;

		node->count++;
		if (node->val > value && node->left == nullptr) {
			Node* n = new Node(value);
			node->left = n;
			updateHeight(node);
			return;
		}

		if (node->val < value && node->right == nullptr) {
			Node* n = new Node(value);
			node->right = n;
			updateHeight(node);
			return;
		}

		if (node->val > value) {
			insert_rec(node->left, value);
		}
		else {
			insert_rec(node->right, value);
		}

		updateHeight(node);
	}

	// min -> max
	// AKA inorder transversal
	void print_values_rec(Node* node) {

		if (node == nullptr) {
			return;
		}

		print_values_rec(node->left);

		std::cout << node->val << " " << node->height << " " << node->count << std::endl;

		print_values_rec(node->right);
	}

	void delete_tree(Node* node) {

		if (node == nullptr)
			return;

		delete_tree(node->left);
		delete_tree(node->right);

		delete node;
	}

	bool is_in_tree_rec(Node* node, int value) {

		if (node == nullptr) {
			return false;
		}

		if (node->val == value) {
			return true;
		}

		if (node->val > value) {
			return is_in_tree_rec(node->left, value);
		}

		return is_in_tree_rec(node->right, value);

	}

	bool valGreaterThan(Node* tree, int value) {
		if (tree == nullptr) {
			return true;
		}

		if (tree->val > value) {
			return false;
		}

		return valGreaterThan(tree->left, value) && valGreaterThan(tree->right, value);
	}

	bool valLesserThan(Node* tree, int value) {
		if (tree == nullptr) {
			return true;
		}

		if (tree->val < value) {
			return false;
		}

		return valLesserThan(tree->left, value) && valLesserThan(tree->right, value);
	}

	bool is_binary_search_tree_rec(Node* node) {
		if (node == nullptr) {
			return true;
		}

		return is_binary_search_tree_rec(node->left) &&
			is_binary_search_tree_rec(node->right) &&
			valGreaterThan(node->left, node->val) &&
			valLesserThan(node->right, node->val);

	}

	Node* successor_for_removal(Node* node) {

		if (node->left == nullptr) {
			return node;
		}

		node->count--;

		Node* retN = successor_for_removal(node->left);

		if (retN == node->left) {
			node->left = nullptr;
		}

		updateHeight(node);

		return retN;
	}

	bool hasNoSubtree(Node* node) {
		return node->left == nullptr && node->right == nullptr;
	}

	bool hasTwoSubtrees(Node* node) {
		return node->left != nullptr && node->right != nullptr;
	}

	int delete_value_rec(Node* node, int value) {

		if (node == nullptr) {
			return -1;
		}

		node->count--;

		Node* toDelete = nullptr;
		bool isLeft = true;
		if (node->left != nullptr && node->left->val == value) {
			toDelete = node->left;
		}
		else if (node->right != nullptr && node->right->val == value) {
			toDelete = node->right;
			isLeft = false;
		}

		if (toDelete != nullptr) {
			int val = toDelete->val;

			if (hasNoSubtree(toDelete)) {
				isLeft ? node->left = nullptr : node->right = nullptr;
			}
			else if (!hasTwoSubtrees(toDelete)) {
				Node* subTree = toDelete->left == nullptr ? toDelete->right : toDelete->left;
				isLeft ? node->left = subTree : node->right = subTree;
			}
			else {
				Node* successor = successor_for_removal(toDelete->right);
				successor->right = successor == toDelete->right? nullptr : toDelete->right;
				successor->left = successor == toDelete->left ? nullptr : toDelete->left;
				successor->count = --toDelete->count;
				updateHeight(successor);
				isLeft ? node->left = successor : node->right = successor;
				delete toDelete;
			}

			updateHeight(node);
			return val;
		}

		int val;
		if (node->val > value) {
			val = delete_value_rec(node->left, value);
		}
		else {
			val = delete_value_rec(node->right, value);
		}

		if (val >= 0) {
			updateHeight(node);
		}

		return val;
	}

public:

	BST() : root(nullptr) {}

	~BST() {
		delete_tree(root);
	}

	void insert(int value) {

		if (root == nullptr) {
			Node* node = new Node(value);
			root = node;
			return;
		}

		insert_rec(root, value);
	}

	int get_node_count() {
		return root == nullptr? 0 : root->count;
	}

	//  Height is the number of NODES 
	// in the longest path starting from the root of the tree
	int get_height() {
		return root == nullptr? 0 : root->height;
	}

	void print_values() {
		print_values_rec(root);
		std::cout << " ";
	}

	bool is_in_tree(int value) {
		return is_in_tree_rec(root, value);
	}

	int get_min() {

		if (root == nullptr)
			return -1;

		Node* node = root;
		for (; node->left != nullptr; node = node->left);

		return node->val;
	}

	int get_max() {

		if (root == nullptr)
			return -1;

		Node* node = root;
		for (; node->right != nullptr; node = node->right);

		return node->val;
	}

	bool is_binary_search_tree(Node* node) {
		return is_binary_search_tree_rec(node);
	}

	bool is_binary_search_tree() {
		return is_binary_search_tree_rec(root);
	}

	int delete_value(int value) {

		if (root->val == value) {
			int val = root->val;
			delete root;
			root = nullptr;
			return val;
		}

		return delete_value_rec(root, value);
	}

	// Return -1 if no successor, successor otherwise
	int get_successor(int value) {

		int min = INT32_MAX;
		
		Node* p = root;
		while (p != nullptr) {
			if (p->val > value && p->val < min) {
				min = p->val;
			}
			if (p->val > value) {
				p = p->left;
			}
			else {
				p = p->right;
			}
		}

		return min == INT32_MAX ? -1 : min;
	}

};

#endif
