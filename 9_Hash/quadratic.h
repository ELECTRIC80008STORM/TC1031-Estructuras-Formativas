#ifndef QUADRATIC_HASH
#define QUADRATIC_HASH

#include <string>
#include <sstream>

using namespace std;

template<typename Key, typename Value>
class Quadratic{
    private:
        Key initValue;
        unsigned int size;
        unsigned int count;
        Key *keys;
        Value *values;
        unsigned int (*func) (const Key);
    
    public:
        Quadratic(unsigned int, Key, unsigned int (*f) (const Key));
        ~Quadratic();
        bool isFull() const;
        void clear();
        void put(const Key, const Value);
        Value get(const Key);
        string toString() const;
};

template<typename Key, typename Value>
Quadratic<Key, Value>::Quadratic(unsigned int size, Key init, unsigned int (*f) (const Key)){
    this->size = size;
    this->count = 0;
    this->initValue = init;
    this->func = f;
    keys = new Key[size];
    values = new Value[size];

    for(int i = 0; i < this->size; i++){
        keys[i] = initValue;
        values[i] = 0;
    }
}

template<typename Key, typename Value>
Quadratic<Key, Value>::~Quadratic(){
    delete [] keys;
    delete [] values;

    keys = nullptr;
    values = nullptr;

    size = 0;
    count = 0;
}

template<typename Key, typename Value>
bool Quadratic<Key, Value>::isFull() const {
    return (count == size);
}

template<typename Key, typename Value>
void Quadratic<Key,Value>::clear(){
    for(int i = 0; i < size; i++){
    keys[i] = initValue;
    values[i] = 0;
    }
}


// Quadratic probing formula
// index = (hash + i * i) % size

template<typename Key, typename Value>
void Quadratic<Key,Value>::put(const Key k, const Value val){
    unsigned int hash = func(k);
    unsigned int index = hash % size;

    if(!isFull()){
        unsigned int aux = 0;
        while(keys[index] != k && keys[index] != initValue){
            index = (hash + aux * aux) % size;
            aux++;
        }
        if(keys[index] == initValue){
            count++;
            keys[index] = k;
        }
        values[index] = val;
    } else{
        for(int i = 0; i < size; i++){
            if(keys[index] == k){
                values[index] = val;
                return;
            }
            index = (hash + i * i) % size;
        }
        // Overflow() exception
    }
}

template<typename Key, typename Value>
Value Quadratic<Key,Value>::get(const Key k){
    unsigned int hash = func(k);
    unsigned int index = hash % size;

    for(int i = 0; i < size && keys[index] != initValue; i++){
        if(keys[index] == k){
            return values[index];
        }
        index = (hash + i * i) % size;
    }
}

// impresion clase quadratic
template<typename Key, typename Value>
string Quadratic<Key, Value>::toString() const {
    stringstream aux;
    for (int i = 0; i < size; i++){
            if (keys[i] != initValue){
                aux << "(" << i << " ";
                aux << keys[i] << " : " << values[i] << ") ";
            }
    }
    return aux.str();
}


#endif