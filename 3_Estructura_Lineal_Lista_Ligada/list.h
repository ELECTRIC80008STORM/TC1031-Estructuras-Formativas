/*
 * linkedlist.h
 *
 *  Created on: 05/08/2015
 *      Author: pperezm
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <string>
#include <sstream>
#include "exception.h"

template <class T> class List;

template <class T>
class Node {
private:
	Node(T);
	Node(T, Node<T>*);
	Node(const Node<T>&);

	T value;
	Node<T>* next;

	friend class List<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), next(nullptr) {}

template <class T>
Node<T>::Node(T val, Node* nxt) : value(val), next(nxt){}

template <class T>
Node<T>::Node(const Node<T>& source) : value(source.value), next(source.next){}

template <class T>
class List {
public:
	List();
	List(const List<T>&) ;
	~List();

	void insertion(T) ;
	int search(T) const;
	bool empty() const;
	void clear();
	std::string toString() const;
	void operator= (const List&);

	void update(int, T);
	T deleteAt(int);

private:
	Node<T>* head;
	int size;
};

template <class T>
List<T>::List(){
	head = nullptr;
	size = 0;
}

template <class T>
List<T>::~List() {
	clear();
}

template <class T>
bool List<T>::empty() const {
	return (size == 0 && head == nullptr);
}

template <class T>
int List<T>::search(T val) const {
	if(!empty()){
		Node<T>* ptr = head;
		int index = 0;
		while(ptr != nullptr){
			if(ptr->value == val){
				return index;
			}
			index++;
			ptr = ptr->next;
		}
	}
	return -1;
}

template <class T>
void List<T>::insertion(T val)  {
	if(empty()){
		head = new Node<T>(val);
	} else{
		Node<T>* ptr = head;
		while (ptr->next != nullptr){
			ptr = ptr->next;
		}
		ptr->next = new Node<T>(val);
	}
	size++;
}

template <class T>
void List<T>::clear() {
	if(empty()){
		return;
	}
	Node<T>* ptr = head->next;
	while (ptr != nullptr){
		delete head;
		head = ptr;
		ptr = ptr->next;
	}
	delete head;
	head = nullptr;
	size = 0;
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Node<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
List<T>::List(const List<T> &source)  {
	if(source.empty()){
		size = 0;
		head = nullptr;
	} else{
		head = new Node<T>(source.head->value);
		size = 1;
		Node<T>* mainPtr = head;
		Node<T>* sourcePtr = source.head;
		while(sourcePtr->next != nullptr){
			mainPtr->next = new Node<T>(sourcePtr->next->value);
			mainPtr = mainPtr->next;
			sourcePtr = sourcePtr->next;
		}
		size = source.size;
	}
}

template <class T>
void List<T>::operator=(const List<T> &source)  {
	if(source.empty()){
		size = 0;
		head = nullptr;
	} else{
		head = new Node<T>(source.head->value);
		size = 1;
		Node<T>* mainPtr = head;
		Node<T>* sourcePtr = source.head;
		while(sourcePtr->next != nullptr){
			mainPtr->next = new Node<T>(sourcePtr->next->value);
			mainPtr = mainPtr->next;
			sourcePtr = sourcePtr->next;
		}
		size = source.size;
	}
}

template <class T>
void List<T>::update(int index, T val)  {
	if(empty()){
		throw(NoSuchElement());
	}
	if(index < 0 || index >= size){
		throw(IndexOutOfBounds());
	}
	Node<T>* ptr = head;
	for(int i = 0; i < index; i++){
		ptr = ptr->next;
	}
	ptr->value = val;
}

template <class T>
T List<T>::deleteAt(int index)  {
	if(empty()){
		throw(NoSuchElement());
	}
	if(index < 0 || index >= size){
		throw(IndexOutOfBounds());
	}
	Node<T>* ptr = head;
	T element;
	if(index == 0){
		head = head->next;
		element = ptr->value;
	} else{
		Node<T>* temp = ptr;
		for(int i = 0; i < index - 1; i++){
			temp = temp->next;
		}
		ptr = temp->next;
		element = ptr->value;
		temp->next = ptr->next;
	}
	delete ptr;
	size--;
	return element;
}

#endif /* LINKEDLIST_H_ */