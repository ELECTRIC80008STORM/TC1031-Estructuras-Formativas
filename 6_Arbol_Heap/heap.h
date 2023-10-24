#ifndef HEAP
#define HEAP

#include <string>
#include <sstream>

template <typename T>
class Heap{
    private:
        T* data;
        unsigned int heapLimit;
        unsigned int count;
        unsigned int parent(unsigned int) const;
        unsigned int left(unsigned int) const;
        unsigned int right(unsigned int) const;
        void heapify(unsigned int);
        void swap(unsigned int, unsigned int);

    public:
        Heap(unsigned int);
        ~Heap();
        bool empty() const;
        bool full() const;
        unsigned int size() const;
        void push(T);
        void pop();
        T top() const;
        void clear();
        std::string toString() const;
};

template <typename T>
Heap<T>::Heap(unsigned int size){
    heapLimit = size;
    data = new T[heapLimit];
    count = 0;
}

template <typename T>
Heap<T>::~Heap(){
    delete [] data;
    data = nullptr;
    heapLimit = 0;
    count = 0;
}

template <typename T>
unsigned int Heap<T>::parent(unsigned int pos) const{
    return ((pos - 1) / 2);
}

template <typename T>
unsigned int Heap<T>::left(unsigned int pos) const{
    return (2 * pos + 1);
}

template <typename T>
unsigned int Heap<T>::right(unsigned int pos) const{
    return (2 * pos + 2);
}

template <typename T>
bool Heap<T>::empty() const{
    return (count == 0);
}

template <typename T>
bool Heap<T>::full() const{
    return (count == heapLimit);
}

template <typename T>
unsigned int Heap<T>::size() const{
    return count;
}

template <typename T>
void Heap<T>::heapify(unsigned int pos){
    unsigned int le = left(pos);
    unsigned int ri = right(pos);
    unsigned int min = pos;

    // Min Heap
    if(le <= count && data[le] < data[pos]){
        min = le;
    }

    if(ri <= count && data[ri] < data[pos] && data[ri] < data[le]){
        min = ri;
    }

    if(min != pos){
        swap(min, pos);
        heapify(min);
    }
}

template <typename T>
void Heap<T>::swap(unsigned int i, unsigned int j){
    T aux = data[i];
    data[i] = data[j];
    data[j] = aux;
}

template <typename T>
void Heap<T>::push(T val){
    if(!full()){
        unsigned int pos = count;
        count++;

        // Min Heap
        while(pos > 0 && data[parent(pos)] > val){
            data[pos] = data[parent(pos)];
            pos = parent(pos);
        }

        data[pos] = val;
    }
}

template <typename T>
void Heap<T>::pop(){
    if(!empty()){
        if(count > 1){
            data[0] = data[--count];
            heapify(0);
        } else{
            clear();
        }
    }
}

template <typename T>
T Heap<T>::top() const{
    if(!empty()){
        return data[0];
    } else{
        return -1;
    }
}

template <typename T>
void Heap<T>::clear(){
    count = 0;
}

template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

#endif