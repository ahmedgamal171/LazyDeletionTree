#pragma once
#include <iostream>
#include <utility>
#include<string>
#include<string.h>
#define nullptr 0

using namespace std;

template <typename Type>
class Lazy_deletion_tree;

template <typename Type>
class Lazy_deletion_node {
private:
	Type data;
	Lazy_deletion_node<Type>* left;
	Lazy_deletion_node<Type>* right;
	bool erased;

public:
	Lazy_deletion_node(Type const& = Type());
	Lazy_deletion_node<Type>* left() const;
	Lazy_deletion_node<Type>* right() const;
	Type retrieve() const;
	int height() const;
	std::pair<Type, bool> front() const;
	std::pair<Type, bool> back() const;
	bool member(Type const&) const;
	void insert(Type const&);
	void erase(Type const&);
	void clear();
	void clean(Lazy_deletion_node*&);

	friend class Lazy_deletion_tree<Type>;
};

// Constructor: creates a new instance of a lazy deletion node.
template <typename Type>
Lazy_deletion_node<Type>::Lazy_deletion_node(Type const& item) {
    data = item;
	left = 0;
	right = 0;
	erased = false;
}

// Left Accessor: returns a pointer to the left subtree of this lazy deletion node.
template <typename Type>
Lazy_deletion_node<Type>* Lazy_deletion_node<Type>::left() const {
	return left;
}

// Right Accessor: returns a pointer to the right subtree of this lazy deletion node.
template <typename Type>
Lazy_deletion_node<Type>* Lazy_deletion_node<Type>::right() const {
	return right;
}

// Retrieve Accessor: returns the object being stored in this lazy deletion node.
template <typename Type>
Type Lazy_deletion_node<Type>::retrieve() const {
	return data;
}

// Height Accessor: returns the height of the subtree with this lazy deletion node as its root.
template <typename Type>
int Lazy_deletion_node<Type>::height() const {
	if (this == 0) {
		return -1;   // Empty subtree has a height of -1.
	}
	int hl, hr;
	else {
		 hl = height(this->left);
		 hr = height(this->right);
		return hl > hr ? hl + 1 : hr + 1;
	}                                          
}                                                                 

// Member Accessor: returns if the object is in and unerased in the subtree with this lazy deletion node as its root node.
template <typename Type>
bool Lazy_deletion_node<Type>::member(Type const& item) const {
	if (this == 0) {
		return false;
	}
	else {
		if (retrieve() == item && !erased) { // Object must not be tagged as erased.
			return true;
		}
		else if (item < retrieve()) {
			return(left()->member(item)); // Recursion.
		}
		else {
			return(right()->member(item)); // Recursion.
		}
	}
}

// Front Accessor: returns the minimum unerased object in the subtree that has this lazy deletion node as its root node.
template <typename Type>
std::pair<Type, bool> Lazy_deletion_node<Type>::front() const {
	if (this == 0) {
		return std::pair<Type, bool>(Type(), false); // Return false if subtree is empty.
	}

	std::pair<Type, bool> result = left()->front(); // First attempt to find minimum object in left subtree of subtree.

	if (result.second) {
		return result;
	}

	if (!erased) {
		return std::pair<Type, bool>(retrieve(), true);
	}

	result = right()->front(); // If minimum object is not in left subtree of subtree, attempt to find it in the right subtree of the subtree.

	if (result.second) {
		return result;
	}

	return std::pair<Type, bool>(Type(), false);

}

// Back Accessor: returns the maximum unerased object in the subtree that has this lazy deletion node as its root node.
// This is a copy of the previous method except with front replaced with back and left and right switched.
template <typename Type>
std::pair<Type, bool> Lazy_deletion_node<Type>::back() const {
	if (this == 0) {
		return std::pair<Type, bool>(Type(), false); // Return false if subtree is empty.
	}

	std::pair<Type, bool> result = right()->back(); // First attempt to find maximum object in right subtree of subtree.

	if (result.second) {
		return result;
	}

	if (!erased) {
		return std::pair<Type, bool>(retrieve(), true);
	}

	result = left()->back(); // If maximum object is not in right subtree of subtree, attempt to find it in the left subtree of the subtree.

	else if
	if (result.second) {
		return result;
	}

	return std::pair<Type, bool>(Type(), false);
}

// Insert Mutator: inserts an object into the subtree or returns false if the object is already inserted.
template <typename Type>
void Lazy_deletion_node<Type>:: insert(Type const& item) {
	if (this == 0) { // Inserting object into an empty subtree.
		data = item;
		cout << "Object"<<item<<" is sucessfully inserted"<<endl;
	} 
	if(retrieve() == item) {
		if (erased) { // Inserting existing object that has been tagged erased.
			erased = false;
			cout << "The object"<<item<<" was erased and now it is inserted"<<endl;
		}
		else {      // Inserting an existing object.
			cout << "You are trying to insert an existing object"<<endl;
		}
	}
	else if (item < retrieve()) { // Inserting object that is less than the current node.
		if (left() == 0) {       // Insert object into left leafnode of current node.
			left = new Lazy_deletion_node<Type>(item);
			cout << "Object"<<item<<" is inserted in left leafnode"<<endl;
		}
		else {
			return(left()->insert(item)); // Recursion.
		}
	}
	else { // Inserting object that is greater than the current node.
		if (right() == 0) { // Insert object into right leafnode of current node.
			right = new Lazy_deletion_node<Type>(item);
			cout << "Object"<<item<<" is inserted in Right leafnode";
		}
		else {
			return(right()->insert(item)); // Recursion.
		}
	}
}

// Erase Mutator: erases an object from the subtree, or returns false if the object is already erased.
template <typename Type>
void Lazy_deletion_node<Type>::erase(Type const& item) {
	if (this == 0) { // Cannot erase from an empty subtree or if reached an empty leaf node.
		cout << "The item is not exist in the tree";
	}
	else if (retrieve() == item) { // Found object to be erased in the subtree.
		if (!erased) { // Perform erase tagging.
			erased = true;
			cout << "The item is erased successfully";

		}
		else { // Cannot erase an already erased object.
			cout << "This item is already erased";
		}
	}
	else if (item < retrieve()) { // Object being erased is less than object in the current node.
		return(left()->erase(item)); // Recursion.
	}
	else { // Object being erased is greater than object in the current node.
		return(right()->erase(item)); // Recursion.
	}
}

// Clear Mutator: deletes all nodes in the subtree.
template <typename Type>
void Lazy_deletion_node<Type>::clear() {
	if (this == 0) {
		return;
	}
	else {
		if (left() != 0) // Check if left subtree of this node is already cleared.
			left()->clear(); // Recursion.
		if (right() != 0) // Check if right subtree of this node is already cleared.
			right()->clear(); // Recursion.

		delete this;
	}
}

// Clean Mutator: deletes all erased tagged nodes in the subtree with this lazy deletion node as its root node.
template <typename Type>
void Lazy_deletion_node<Type>::clean(Lazy_deletion_node*&node_ptr) {
	if (this == 0) {
		return; // Cannot clean an empty subtree or a node that is a nullptr (already deleted).
	}
	else if (erased) { // Found node to be cleaned.
		if ((right()->front()).second) {
			element = (right()->front()).first; // If possible replace this node with the front of its right subtree.
			erased = false;
			right()->erase(element); // Erase copied node (front of right subtree).
		}
		else if ((left()->back()).second) {
			element = (left()->back()).first; // Else if possible replace this node with the back of its left subtree.
			erased = false;
			left()->erase(element); // Erase copied node (back of left subtree).
		}
		else {
			// Do nothing.
		}
	}
	else {
		// Do nothing;
	}

	left()->clean(left); // Recursion.
	right()->clean(right); // Recursion.

	if (erased) { // If this node has not been replaced by a node from one of the subtrees then delete it.
		node_ptr = 0;
		delete this;
	}
}

