#include<iostream>
#include"Lazy_deletion_node.h"
#include"Lazy_deletion_tree.h"


int main() {
	Lazy_deletion_tree<int> tree;
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.breadth_first_traversal();

	
}



