
#include <stdexcept>

// AVL Node Clas
template<class T, class V>
class AVLTreeNode {
public:
	// Should have attributes named:
	// parent - pointer to parent
	// left - pointer to left child
	// right - pointer to right child
	AVLTreeNode *parent, *left, *right;
	// key - node's key
	T key;
	// value - node's value
	V value;
	// height - node's height
	int depth;
	int balance;

	// Constructors ...
	AVLTreeNode(T key, V value, AVLTreeNode *parent, AVLTreeNode *left, AVLTreeNode *right) : 
	key(key), value(value), parent(parent), left(left), right(right) { depth = 0; balance = 0; };


};

// AVL Tree class
template <class T, class V>
class AVLTree
{
private:
	// Tree attributes go here
	// Your tree MUST have a root node named root
	AVLTreeNode<T, V> *root;
	bool insert(AVLTreeNode<T, V>*& root, T key, V value);
	void computeBalance(AVLTreeNode<T, V> *root);
	void balance(AVLTreeNode<T, V>*& root);
	void balanceLeft(AVLTreeNode<T, V>*& root);
	void balanceRight(AVLTreeNode<T, V>*& root);
	void rotateLeft(AVLTreeNode<T, V>*& root);
	void rotateRight(AVLTreeNode<T, V>*& root);
	V find(AVLTreeNode<T, V>* root, T key);
	void _remove(AVLTreeNode<T, V>*& root, T key, bool& del);
	void _RemoveBothChildren(AVLTreeNode<T, V>*& root, AVLTreeNode<T, V>*& curr, bool& del);
	AVLTreeNode<T, V>* removal(AVLTreeNode<T, V>* root, T key, bool& del);
	T findMin(AVLTreeNode<T, V>* root);
	T findMax(AVLTreeNode<T, V>* root);


	void preorder(AVLTreeNode<T, V>* root);

	unsigned int count;
	unsigned int duplicate = 0;

public:

	AVLTree(); // constructor
	AVLTree(const AVLTree& av); // copy
	AVLTree& operator=(const AVLTree& av); // operator
	//~AVLTree(); // destructor

	bool insert(T key, V value);
	bool remove(T key);
	V search(T key);
	unsigned int size();

	void* getRoot() const { return root; }; // DO NOT REMOVE
};

// AVL Tree Methods go here
template <class T, class V>
AVLTree<T, V>::AVLTree() {
	root = NULL;
	count = 0;
}

template <class T, class V>
bool AVLTree<T, V>::insert(T key, V value) {
	if (root == NULL) {
		root = new AVLTreeNode<T, V>(key, value, NULL, NULL, NULL);
		count++;
		return true;
	}
	duplicate = 0;
	return insert(root, key, value);
}

template <class T, class V>
bool AVLTree<T, V>::insert(AVLTreeNode<T, V>*& root, T key, V value) {
	/*
	if (tree == NULL) {
		count++;
		return new AVLTreeNode(key, value, NULL, NULL, NULL);
	} */
	/*
	if (key <= tree->key) { // left subtree
		tree->left = insert(tree->left, key, value);
		// assert(tree->left);
		tree->left->parent = tree;
		tree->left->depth = tree->depth + 1;
	} else { // right subtree
		tree->right = insert(tree->right, key, value);
		// assert(tree->right);
		tree->right->parent = tree;
		tree->right->depth = tree->depth + 1;
	}

	return tree; */

	if (key < root->key) {
		if (root->left) {
			insert(root->left, key, value);
		} else {
			root->left = new AVLTreeNode<T, V>(key, value, NULL, NULL, NULL);
			count++;
		}
	}
	else if (key > root->key) {
		if (root->right) {
			insert(root->right, key, value);
		} else {
			root->right = new AVLTreeNode<T, V>(key, value, NULL, NULL, NULL);
			count++;
		}
	}
	else { // duplicate key
		duplicate++;
	}

	if (duplicate > 0) {
		//duplicate = 0;
		return false;
	}

	computeBalance(root);
	balance(root);
	return true;
}

template <class T, class V>
void AVLTree<T, V>::computeBalance(AVLTreeNode<T, V>* root) {
	if (root) {
		int leftDepth  = root->left  ? root->left->depth  : -1;
		int rightDepth = root->right ? root->right->depth : -1;

		root->depth = 1 + ((leftDepth > rightDepth) ? leftDepth : rightDepth);
		root->balance = rightDepth - leftDepth;
	}
}

template <class T, class V>
void AVLTree<T, V>::balance(AVLTreeNode<T, V>*& root) {
	if (root->balance > 1) {
		balanceRight(root);
	}
	if (root->balance < -1) {
		balanceLeft(root);
	}
}

template <class T, class V>
void AVLTree<T, V>::balanceRight(AVLTreeNode<T, V>*& root) {
	if (root->right) {
		if (root->right->balance > 0) {
			rotateLeft(root);
		}
		else if (root->right->balance < 0) {
			rotateRight(root->right);
			rotateLeft(root);
		}
	}
}

template <class T, class V>
void AVLTree<T, V>::balanceLeft(AVLTreeNode<T, V>*& root) {
	if (root->left) {
		if (root->left->balance < 0) {
			rotateRight(root);
		}
		else if (root->left->balance > 0) {
			rotateLeft(root->left);
			rotateRight(root);
		}
	}
}

template <class T, class V>
void AVLTree<T, V>::rotateLeft(AVLTreeNode<T, V>*& root) {
	AVLTreeNode<T, V>* temp = root;
	root = root->right;
	temp->right = root->left;
	root->left = temp;

	computeBalance(root->left);
	computeBalance(root->right);
	computeBalance(root);
}

template <class T, class V>
void AVLTree<T, V>::rotateRight(AVLTreeNode<T, V>*& root) {
	AVLTreeNode<T, V>* temp = root;
	root = root->left;
	temp->left = root->right;
	root->right = temp;

	computeBalance(root->left);
	computeBalance(root->right);
	computeBalance(root);
}

template <class T, class V>
bool AVLTree<T, V>::remove(T key) {
	bool del = false;
	//_remove(root, key, del);
	removal(root, key, del);
	//count--;
	if (del == true) {
		count--;
	}
	return del;
}

template <class T, class V>
void AVLTree<T, V>::_remove(AVLTreeNode<T, V>*& root, T key, bool& del) {
	if (!root) {
		del = false;
	}
	else if (root->key > key) {
		_remove(root->left, key, del);
		if (del) {
			computeBalance(root);
			balanceRight(root);
		}
	}
	else if (root->key < key) {
		_remove(root->right, key, del);
		if (del) {
			computeBalance(root);
			balanceLeft(root);
		}
	}
	else {
		AVLTreeNode<T, V>* temp = root;
		if (!root->left) {
			root = root->left;
			del = true;
			delete temp;
		}
		else if (!root->left) {
			root = root->right;
			del = true;
			delete temp;
		}
		else {
			_RemoveBothChildren(root, root->left, del);
			if (del) {
				computeBalance(root);
				balance(root);
			}
			del = true;
		}
	}
}

template<class T, class V>
void AVLTree<T, V>::_RemoveBothChildren(AVLTreeNode<T, V>*& root, AVLTreeNode<T, V>*& curr, bool& del)
{
	if (!curr->right)
	{
		root->key = curr->key;
		root->value = curr->value;
		AVLTreeNode<T, V>* pMe = curr;
		curr = curr->left;
		delete pMe;
		del = true;
	}
	else
	{
		_RemoveBothChildren(root, curr->right, del);
		if (del)
		{
			computeBalance(root);
			balance(root);
		}
	}
}

template <class T, class V>
AVLTreeNode<T, V>* AVLTree<T, V>::removal(AVLTreeNode<T, V>* root, T key, bool& del) {
	if (root == NULL) {
		return NULL;
	}

	if (key < root->key) {
		root->left = removal(root->left, key, del);
	}
	else if  (key > root->key) {
		root->right = removal(root->right, key, del);
	} else { // key found
		del = true;
		if (root->left == NULL) {
			return root->right;
		}
		else if (root->right == NULL) {
			return root->left;
		} else {
			if (root->left->depth > root->right->depth) {
				T temp = findMax(root->left);
				root->key = temp;
				root->left = removal(root->left, temp, del);
			} else {
				T temp = findMin(root->right);
				root->key = temp;
				root->right = removal(root->right, temp, del);
			}
		}
	}
	computeBalance(root);
	balance(root);
	return root;
}

template <class T, class V>
T AVLTree<T, V>::findMax(AVLTreeNode<T, V>* root) {
	while (root->right != NULL) {
		root = root->right;
	}
	return root->key;
}

template <class T, class V>
T AVLTree<T, V>::findMin(AVLTreeNode<T, V>* root) {
	while (root->left != NULL) {
		root = root->left;
	}
	return root->key;
}

template <class T, class V>
V AVLTree<T, V>::search(T key) {
	return find(root, key);
}

template <class T, class V>
V AVLTree<T,V>::find(AVLTreeNode<T, V>* root, T key) {
	if (root) {
		if (root->key == key) {
			return root->value;
		}
		if (key < root->key) {
			return find(root->left, key);
		} else {
			return find(root->right, key);
		}
	} else {
		throw std::runtime_error("Key not found");
	}
}


// Returns number of items stored in a tree
template <class T, class V>
unsigned int AVLTree<T, V>::size() {
	//std::cout << root->key << " " << root->value << std::endl;
	preorder(root);
	std::cout << std::endl;
	return count;
}

template <class T, class V>
void AVLTree<T, V>::preorder(AVLTreeNode<T, V> *root)
{
    if(root != NULL)
    {
        std::cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}