#ifndef DOUBLELINKLIST
#define DOUBLELINKLIST

#include <string>
#include <sstream>

template <class T> class DList;

template <class T>
class Node {
private:
	Node(T);
	Node(T, Node<T>*, Node<T>*);
	Node(const Node<T>&);

	T value;
	Node<T>* previous;
	Node<T>* next;

	friend class DList<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), previous(0), next(0) {}

template <class T>
Node<T>::Node(T val, Node *prev, Node* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
Node<T>::Node(const Node<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

template <class T>
class DList {
public:
	DList();
	DList(const DList<T>&);
	void operator= (const DList&);
	~DList();

	int length() const;
	bool empty() const;
	void insertion(T);
	void clear();
	int search(T) const;
	void update(int, T);
	T deleteAt(int);
	std::string toStringForward() const;
	std::string toStringBackward() const;

private:
	Node<T>* head;
	Node<T>* tail;
	int size;

};

template <class T>
DList<T>::DList() : head(nullptr), tail(nullptr), size(0) {}

template <class T>
DList<T>::DList(const DList<T> &source)  {
	if(source.empty()){
		head = nullptr;
		tail = nullptr;
		size = 0;
	} else{
		head = new Node<T>(source.head->value, nullptr, nullptr);
		Node<T>* originalPtr = head;
		Node<T>* sourcePtr = source.head;
		for(int i = 1; i < source.size; i++){
			sourcePtr = sourcePtr->next;
			originalPtr->next = new Node<T>(sourcePtr->value, originalPtr, nullptr);
			originalPtr = originalPtr->next;
		}
		tail = originalPtr;
		size = source.size;
	}
}

template <class T>
void DList<T>::operator=(const DList<T> &source)  {
	clear();
	if(source.empty()){
		head = nullptr;
		tail = nullptr;
		size = 0;
	} else{
		head = new Node<T>(source.head->value, nullptr, nullptr);
		Node<T>* originalPtr = head;
		Node<T>* sourcePtr = source.head;
		for(int i = 1; i < source.size; i++){
			sourcePtr = sourcePtr->next;
			originalPtr->next = new Node<T>(sourcePtr->value, originalPtr, nullptr);
			originalPtr = originalPtr->next;
		}
		tail = originalPtr;
		size = source.size;
	}
}

template <class T>
DList<T>::~DList() {
	clear();
}

template <class T>
int DList<T>::length() const {
	return size;
}

template <class T>
bool DList<T>::empty() const {
	return (head == nullptr && tail == nullptr && size == 0);
}

template <class T>
void DList<T>::insertion(T val)  {
	if(empty()){
		head = new Node<T>(val);
		tail = head;
	} else{
		tail->next = new Node<T>(val, tail, nullptr);
		tail = tail->next;
	}
	size++;
}

template <class T>
void DList<T>::clear() {
	Node<T>* mainPtr = head;
	Node<T>* auxPtr = mainPtr;
	if(!empty()){
		while(mainPtr != nullptr){
			auxPtr = mainPtr;
			mainPtr = mainPtr->next;
			delete auxPtr;
		}
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
}

template <class T>
int DList<T>::search(T val) const {
	Node<T>* ptr = head;
	int counter = 0;
	if(!empty()){
		while(ptr != nullptr){
			if(ptr->value == val){
				return counter;
			}
			ptr = ptr->next;
			counter++;
		}
	}
	return -1;
}

template <class T>
void DList<T>::update(int index, T val){
	Node<T>* ptr = head;
	for(int i = 0; i < index; i++){
		ptr = ptr->next;
	}
	ptr->value = val;
}

template <class T>
T DList<T>::deleteAt(int index)  {
	Node<T>* ptr = head;
	T element;
	if(size == 1){
		head = nullptr;
		tail = nullptr;
	} 
	else if(index != 0){
		Node<T>* temp = ptr;
		for(int i = 0; i < index - 1; i++){
			temp = temp->next;
		}
		ptr = temp->next;
		if(ptr == tail){
			tail = temp;
			temp->next = temp->next->next;
		} else{
			temp->next = temp->next->next;
			temp->next->previous = temp;
		}
	} else{
		head = ptr->next;
		head->previous = nullptr;
	}
	element = ptr->value;
	delete ptr;
	size--;
	return element;
}

template <class T>
std::string DList<T>::toStringForward() const {
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
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	Node<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

#endif /* DOUBLELINKLIST */
