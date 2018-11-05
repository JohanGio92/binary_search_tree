#include <iostream>

#include "BinarySearchTree.h"

using namespace std;

int main() {
	BinarySearchTree<int>* binarySearchTree = new BinarySearchTree<int>(5);
	binarySearchTree->insert(4);
	binarySearchTree->insert(6);
	binarySearchTree->insert(8);
	binarySearchTree->insert(3);
	binarySearchTree->remove(binarySearchTree->begin(), 8);
	binarySearchTree->levelOrder();
	delete binarySearchTree;
	return 0;
}
