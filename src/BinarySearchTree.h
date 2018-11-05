#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include "Node.h"
#include <queue>
#include <iostream>
#include <algorithm>

template <class T>
class BinarySearchTree {
private:
	Node<T>* head;
public:
	BinarySearchTree(T data);
	Node<T>* begin();
	void insert(T data);
	Node<T>* search(Node<T>* iterator, T data);
	Node<T>* remove(Node<T> *iterator, T data);
	void levelOrder();
	void preOrder(Node<T> *iterator);
	void inOrder(Node<T> *iterator);
	void postOrder(Node<T> *iterator);
	Node<T>* findMax(Node<T> *iterator);
	Node<T>* findMin(Node<T> *iterator);
	int getHeight(Node<T> *head);
	virtual ~BinarySearchTree();
private:
	Node<T>* insert(Node<T> *head, T data);
	void destroy(Node<T>* node);
	bool isEmpty(Node<T>*& head);
};

template<class T>
inline BinarySearchTree<T>::BinarySearchTree(T data) {
	head = new Node<T>(data);
}

template<class T>
Node<T>* BinarySearchTree<T>::search(Node<T>* iterator, T data) {
	bool ok = false;
	while(!isEmpty(iterator) && !ok){
		if(data == iterator->getData()) ok = true;
		else if (data < iterator->getData()) iterator = iterator->getLeft();
		else iterator = iterator->getRight();
	}
	return iterator;
}

template<class T>
Node<T>* BinarySearchTree<T>::begin() {
	return head;
}

template<class T>
void BinarySearchTree<T>::destroy(Node<T>* node) {
	if(!isEmpty(node)){
		this->destroy(node->getLeft());
		this->destroy(node->getRight());
		delete node;
	}
}

template<class T>
Node<T>* BinarySearchTree<T>::remove(Node<T>* iterator, T data) {
	if (isEmpty(iterator)){
		return iterator;
	} else if(data < iterator->getData()){
		iterator->setLeft(this->remove(iterator->getLeft(), data));
	} else if(data > iterator->getData()){
		iterator->setRight(this->remove(iterator->getRight(), data));
	} else{
		if(isEmpty(iterator->getLeft()) && isEmpty(iterator->getRight())){
			delete iterator;
			iterator = nullptr;
		} else if(isEmpty(iterator->getLeft())){
			Node<T>* previous = iterator;
			iterator = iterator->getRight();
			delete previous;
		} else if (isEmpty(iterator->getRight())) {
			Node<T>* previous = iterator;
			iterator = iterator->getLeft();
			delete previous;
		} else {
			Node<T>* previos = this->findMin(iterator);
			iterator->setData(previos->getData());
			iterator->setRight(
					this->remove(iterator->getRight(), iterator->getData()));
		}
	}
	return iterator;
}

template<class T>
bool BinarySearchTree<T>::isEmpty(Node<T>*& head){
	return head == nullptr;
}

template<class T>
Node<T>* BinarySearchTree<T>::insert(Node<T> *iterator, T data) {
	if (isEmpty(iterator)) {
		iterator = new Node<T>(data);
	} else if(data <= iterator->getData()){
		iterator->setLeft(this->insert(iterator->getLeft(), data));
	} else {
		iterator->setRight(this->insert(iterator->getRight(), data));
	}
	return iterator;
}

template<class T>
void BinarySearchTree<T>::insert(T data) {
	head = this->insert(this->begin(), data);
}

template<class T>
void BinarySearchTree<T>::preOrder(Node<T> *iterator) {
	if(!isEmpty(iterator)){
		std::cout << iterator->getData() << std::endl;
		this->preOrder(iterator->getLeft());
		this->preOrder(iterator->getRight());
	}
}

template<class T>
void BinarySearchTree<T>::inOrder(Node<T> *iterator) {
	if (!isEmpty(iterator)) {
		this->inOrder(iterator->getLeft());
		std::cout << iterator->getData() << std::endl;
		this->inOrder(iterator->getRight());
	}
}

template<class T>
void BinarySearchTree<T>::postOrder(Node<T> *iterator) {
	if (!isEmpty(iterator)) {
		this->postOrder(iterator->getLeft());
		this->postOrder(iterator->getRight());
		std::cout << iterator->getData() << std::endl;
	}
}

template<class T>
void BinarySearchTree<T>::levelOrder() {
	std::queue<Node<T>*> queue;
	queue.push(head);
	while (!queue.empty()) {
		Node<T>* iterator = queue.front();
		queue.pop();
		std::cout << iterator->getData() << std::endl;
		if(iterator->getLeft() != nullptr) queue.push(iterator->getLeft());
		if(iterator->getRight() != nullptr) queue.push(iterator->getRight());
	}
}

template<class T>
Node<T>* BinarySearchTree<T>::findMax(Node<T> *iterator) {
	while(!isEmpty(iterator->getRight())){
		iterator = iterator->getRight();
	}
	return iterator;
}

template<class T>
Node<T>* BinarySearchTree<T>::findMin(Node<T> *iterator) {
	while (!isEmpty(iterator->getLeft())) {
		iterator = iterator->getLeft();
	}
	return iterator;
}

template<class T>
int BinarySearchTree<T>::getHeight(Node<T> *iterator) {
	if (isEmpty(iterator)) {
		return -1;
	}
	return std::max(getHeight(iterator->getLeft()), getHeight(iterator->getRight())) + 1;
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
	this->destroy(head);
}

#endif
