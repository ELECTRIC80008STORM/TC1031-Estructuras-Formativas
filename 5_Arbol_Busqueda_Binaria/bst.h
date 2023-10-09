#ifndef BST_H
#define BST_H

#include <string>
#include <sstream>
#include <queue>

template<typename T>
class Node {
    private:
        T value;
        Node<T> *left, *right;

    public:
        Node(T);
        Node(T, Node<T>*, Node<T>*);
        void add(T);
        void preorder(std::stringstream&) const;
        void inorder(std::stringstream&) const;
        void postorder(std::stringstream&) const;
        void levelorder(std::stringstream&);
        unsigned int height();
        void ancestors(unsigned int, std::stringstream&) const;
        unsigned int whatlevelamI(T);
        void removeChilds();
};

template<typename T>
Node<T>::Node(T val) : value(val), left(nullptr), right(nullptr) {}

template<typename T>
Node<T>::Node(T val, Node<T>* left, Node<T>* right) : value(val), left(left), right(right) {}

template<typename T>
void Node<T>::add(T val){
    if(val < value){
        if(left != nullptr){
            left->add(val);
        } else{
            left = new Node<T>(val);
        }
    } else if(val > value){
        if(right != nullptr){
            right->add(val);
        } else{
            right = new Node<T>(val);
        }
    }
}

template<typename T>
void Node<T>::preorder(std::stringstream& aux) const{
    aux << value;
    if(left != nullptr){
        aux << " ";
        left->preorder(aux);
    }

    if(right != nullptr){
        aux << " ";
        right->preorder(aux);
    }
}

template<typename T>
void Node<T>::inorder(std::stringstream& aux) const{
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template<typename T>
void Node<T>::postorder(std::stringstream& aux) const{
    if(left != nullptr){
        left->postorder(aux);
    }

    if(right != nullptr){
        right->postorder(aux);
    }
	
    if (aux.tellp() != 1) {
		aux << " ";
	}
    aux << value;
}

template<typename T>
void Node<T>::levelorder(std::stringstream& aux){
    std::queue< Node<T>* > auxiliarQueue;

    auxiliarQueue.push(this);

    while(!auxiliarQueue.empty()){
        Node<T>* current = auxiliarQueue.front();
        auxiliarQueue.pop();

        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << current->value;

        if (current->left != nullptr) {
            auxiliarQueue.push(current->left);
        }

        if (current->right != nullptr) {
            auxiliarQueue.push(current->right);
        }
    }
}

template<typename T>
unsigned int Node<T>::height(){
    std::queue< Node<T>* > auxiliarQueue;
    unsigned int height = 0;

    auxiliarQueue.push(this);
    while (!auxiliarQueue.empty()) {
        int size = auxiliarQueue.size();
        
        for (int i = 0; i < size; i++){
            Node<T>* current = auxiliarQueue.front();
            auxiliarQueue.pop();
            if (current->left != nullptr) {
                auxiliarQueue.push(current->left);
            }
            if (current->right != nullptr) {
                auxiliarQueue.push(current->right);
            }
        }
        height++;
    }
    return height;
}

template<typename T>
void Node<T>::ancestors(unsigned int val, std::stringstream& aux) const{
	if(value == val){
		return;
	} else if(val < value){
        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << value;
        if(left != nullptr){
            left->ancestors(val, aux);
        } else{
            aux.str("");
            aux << "[";
            return;
        }
	} else if(val > value){
        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << value;
        if(right != nullptr){
            right->ancestors(val, aux);
        } else{
            aux.str("");
            aux << "[";
            return;
        }
	}
}

template<typename T>
unsigned int Node<T>::whatlevelamI(T val){
    std::queue< Node<T>* > auxiliarQueue;
    unsigned int currentLevel = 1;

    auxiliarQueue.push(this);

    while(!auxiliarQueue.empty()) {
        int size = auxiliarQueue.size();

        for (int i = 0; i < size; i++) {
            Node<T>* current = auxiliarQueue.front();
            auxiliarQueue.pop();

            if (current->value == val) {
                return currentLevel;
            }

            if (current->left != nullptr) {
                auxiliarQueue.push(current->left);
            }

            if (current->right != nullptr) {
                auxiliarQueue.push(current->right);
            }
        }
        currentLevel++;
    }
    return 0;
}

template<typename T>
void Node<T>::removeChilds(){
    if(left != nullptr){
        left->removeChilds();
        delete left;
        left = nullptr;
    } else if(right != nullptr){
        right->removeChilds();
        delete right;
        right = nullptr;
    }
}

template<typename T>
class BST{
    private:
        Node<T>* root;

    public:
        BST();
        ~BST();
        bool empty() const;
        void add(T);
        std::string visit() const;
        unsigned int height() const;
        std::string ancestors(unsigned int) const;
        unsigned int whatlevelamI(T) const;
        void removeAll();
};

template<typename T>
BST<T>::BST() : root(nullptr) {}

template<typename T>
BST<T>::~BST(){
    removeAll();
}

template<typename T>
bool BST<T>::empty() const{
    return (root == nullptr);
}

template<typename T>
void BST<T>::add(T val){
    if(root == nullptr){
        root = new Node<T>(val);
    } else{
        root->add(val);
    }
}

template<typename T>
std::string BST<T>::visit() const{
	std::stringstream aux, aux2, aux3, aux4;

	aux << "[";
	root->preorder(aux);
    aux << "]" << std:: endl;

    aux2 << "[";
    root->inorder(aux2);
    aux2 << "]" << std:: endl;

    aux3 << "[";
    root->postorder(aux3);
    aux3 << "]" << std:: endl;

	aux4 << "[";
	root->levelorder(aux4);
    aux4 << "]";

    aux << aux2.str() << aux3.str() << aux4.str();
    return aux.str();
}

template<typename T>
unsigned int BST<T>::height() const{
    if(!empty()){
        return root->height();
    } else{
        return 0;
    }
}

template<typename T>
std::string BST<T>::ancestors(unsigned int val) const{
    std::stringstream aux;
    if(!empty()){
        aux << "[";
        root->ancestors(val, aux);
        aux << "]";
        return aux.str();
    }
}

template<typename T>
unsigned int BST<T>::whatlevelamI(T val) const{
    if(!empty()){
        return root->whatlevelamI(val);
    } else{
        return 0;
    }
}

template<typename T>
void BST<T>::removeAll(){
	if(!empty()){
		root->removeChilds();
		delete root;
		root = nullptr;
	}
}

#endif