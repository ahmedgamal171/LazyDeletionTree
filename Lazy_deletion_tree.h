#pragma once
#include <queue>
#include<iostream>
#include "Lazy_deletion_node.h"
using namespace std;

template <typename Type>
class Lazy_deletion_tree {
private:
	Lazy_deletion_node<Type>* root;
	int count;
public:
	Lazy_deletion_tree();
	~Lazy_deletion_tree();

	bool empty() const;
	int size() const;
	int height() const;
	Type front() const;
	Type back() const;
	bool member(Type const&) const;
	void breadth_first_traversal() const;

	void insert(Type const&);
	void erase(Type const&);
	void clean();
	void clear();
};

// Constructor: creates a new instance of the lazy deletion tree data structure.
template <typename Type>
Lazy_deletion_tree<Type>::Lazy_deletion_tree() :
	root(0),
	count(0) {
	// Only initializes member variables
}

// Destructor: returns any memory that was allocated by the lazy deletion tree constructor.
template <typename Type>
Lazy_deletion_tree<Type>::~Lazy_deletion_tree() {
	clear(); // Calling clear on the root node will delete all nodes of the lazy deletion tree.
}

// Breadth First Traversal Accessor: performs a breadth first traversal and prints objects in order that they're visited.
template <typename Type>
void Lazy_deletion_tree<Type>::breadth_first_traversal() const {
	if (root == 0) {
		return;
	}
	std::queue< Lazy_deletion_node<Type>*> queue;

	queue.push(root);

	// Push nodes on the queue, then print object, then pop it off and push on its children. Repeat to display entire tree.
	while (!queue.empty()) {
		Lazy_deletion_node<Type>* current = queue.front();
		if (current->erased) {
			cout << current->retrieve() << "x "; // Print x next to object if it is marked as erased.
		}
		else {
			cout << current->retrieve() << " ";
		}

		queue.pop();

		if (current->left() != 0) // Check if there is a left child.
			queue.push(current->left());

		if (current->right() != 0) // Check if there is a right child.
			queue.push(current->right());
	}
}

// Empty Accessor: returns true if the size of the lazy deletion tree is 0.
template <typename Type>
bool Lazy_deletion_tree<Type>::empty() const {
	return(size() == 0);
}

// Size Accessor: returns how many unerased objects are in the lazy deletion tree.
template <typename Type>
int Lazy_deletion_tree<Type>::size() const {
	return count;
}

// Height Accessor: returns the height of the lazy deletion tree (also including erased nodes).
template <typename Type>
int Lazy_deletion_tree<Type>::height() const {
	return(root->height());
}

// Member Accessor: returns true if the object can be found in the lazy deletion tree and is not erased.
template <typename Type>
bool Lazy_deletion_tree<Type>::member(Type const& obj) const {
	return(root->member(obj));
}

// Front Accessor: returns the minimum unerased element of the lazy deletion tree, false if there is none.
template <typename Type>
Type Lazy_deletion_tree<Type>::front() const {
	if (empty()) {
		throw underflow(); // Throw underflow incase the tree is empty.
	}
	else {
		return((root->front()).first);
	}
}

// Back Accessor: returns the maximum unerased element of the lazy deletion tree, false if there is none.
template <typename Type>
Type Lazy_deletion_tree<Type>::back() const {
	if (empty()) {
		throw underflow(); // Throw underflow incase the tree is empty.
	}
	else {
		return((root->back()).first);
	}
}

// Insert Mutator: inserts an object into the lazy deletion tree or returns false if the object is already inserted.
template <typename Type>
void Lazy_deletion_tree<Type>::insert(Type const& obj) {
	if (root== 0) {
		++count;
		root = new Lazy_deletion_node<Type>(obj); // If no root node exists yet, create a new one.
		cout << "The item is" << obj << " inserted successfully" <<endl ;
	}
	else if (root->insert(obj)) {
		++count;
		cout << "The item is" << obj << " inserted successfully" << endl;

	}
	else {
		cout << "The item is" << obj << " already in the tree" << endl;
		// Object is already in the tree.
	}
}

// Erase Mutator: erases an object from the lazy deletion tree, or returns false if the object is already erased.
template <typename Type>
void Lazy_deletion_tree<Type>::erase(Type const& obj) {
	if (root == 0) {
		cout << "The tree is empty"; // Tree is empty, therefore nothing can be erased.
	}
	else if (root->erase(obj)) {
		--count;
		cout << "The item is erased successfully";
	}
	else {
		cout<<"The item is already in the tree" // Object has already been erased.
	}
}

// Clear Mutator: deletes all the nodes in the lazy deletion tree.
template <typename Type>
void Lazy_deletion_tree<Type>::clear() {
	if (root == 0) {
		return;
	}
	else {
		root->clear(); // Deletes all nodes in the tree.
		root = 0; // Must set the root_node to a nullptr after deleting all nodes.
		count = 0;
	}
}

// Clean Mutator: deletes all objects of the lazy deletion tree that have been tagged as erased.
template <typename Type>
void Lazy_deletion_tree<Type>::clean() {
	root->clean(root);
}