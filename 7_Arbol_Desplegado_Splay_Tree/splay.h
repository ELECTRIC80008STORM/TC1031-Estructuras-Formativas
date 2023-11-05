#ifndef SPLAY
#define SPLAY

#include <string>
#include <sstream>
#include <iostream>

template <typename T> class SplayTree;

template <typename T>
class Node {
private:
	T value;
	Node *left, *right, *parent;

	Node<T>* succesor();
	void rot_right(Node<T>*);
	void rot_left(Node<T>*);

public:
	Node(T);
	Node(T, Node<T>*, Node<T>* ,Node<T>*);
	Node<T>* add(T);
	Node<T>* find(T);
	Node<T>* remove(T);
	void removeChilds();
    Node<T>* splay(Node<T>*, Node<T>*);
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;

	friend class SplayTree<T>;
};

template<typename T>
Node<T>::Node(T val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}

template<typename T>
Node<T>::Node(T val, Node<T>* le, Node<T>* ri, Node<T>* p) : 
value(val), left(le), right(ri), parent(p) {}

template<typename T>
Node<T>* Node<T>::add(T val){
    if(val < value){
        if(left != nullptr){
            return left->add(val);
        } else{
            left = new Node<T>(val, nullptr, nullptr, this);
            return left;
        }
    } else if(val > value){
        if(right != nullptr){
            return right->add(val);
        } else{
            right = new Node<T>(val, nullptr, nullptr, this);
            return right;
        }
    }
    return this;
}

template<typename T>
Node<T>* Node<T>::find(T val){
    if(val < value && left != nullptr){
        return left->find(val);
    } else if(val > value && right != nullptr){
        return right->find(val);
    }
    return this;
}

template<typename T>
Node<T>* Node<T>::succesor(){
    Node<T> *le = left, *ri = right;

    if(right == nullptr){
        if(left != nullptr){
            left = nullptr;
            le->parent = nullptr;
        }
        return le;
    }

    if(right->left == nullptr){
        right = right->right;
        ri->right = nullptr;
        ri->parent = nullptr;
        return ri;
    }

    Node<T> *parent = right, *child = right->left;
    while (child->left != nullptr){
        parent = child;
        child = child->left;
    }
    parent->left = child->right;
    child->right = nullptr;
    child->parent = nullptr;
    return child;
}

template<typename T>
Node<T>* Node<T>::remove(T val){
    Node<T> *oldNode, *succesorNode;
    oldNode = nullptr;
    succesorNode = nullptr;

    if(val < value){
        if(left){
            if(left->value == val){
                oldNode = left;
                succesorNode = oldNode->succesor();
                if(succesorNode){
                    if(oldNode->left != succesorNode){
                        succesorNode->left = oldNode->left;
                    } else if(oldNode->right != succesorNode){
                        succesorNode->right = oldNode->right;
                    }         
                    if(succesorNode->left){
                        succesorNode->left->parent = succesorNode;
                    }
                    if(succesorNode->right){
                        succesorNode->right->parent = succesorNode;
                    }
                    succesorNode->parent = oldNode->parent;
                }
                left = succesorNode;
                delete oldNode;
                return this;
            } else{
                return left->remove(val);
            }
        }
    } else if(val > value){
        if(right){
			if(right->value == val){
				oldNode = right;
				succesorNode = oldNode->succesor();
				if(succesorNode){
					if(oldNode->left != succesorNode){
                        succesorNode->left = oldNode->left;
                    } else if(oldNode->right != succesorNode){
                        succesorNode->right = oldNode->right;
                    }
                    if(succesorNode->left){
                        succesorNode->left->parent = succesorNode;
                    }
                    if(succesorNode->right){
                        succesorNode->right->parent = succesorNode;
                    }
                    succesorNode->parent = oldNode->parent;
				}
                right = succesorNode;
                delete oldNode;
                return this;
			} else{
				return right->remove(val);
			}
        }
    }
}

template<typename T>
void Node<T>::removeChilds() {
    if(left != nullptr) {
        left->removeChilds();
        delete left;
        left = nullptr;
    }
    if(right != nullptr) {
        right->removeChilds();
        delete right;
        right = nullptr;
    }
}

template<typename T>
void Node<T>::rot_right(Node<T>* x){
    Node<T>* y = x->left;
    x->left = y->right;
    if(x->left){
        x->left->parent = x;
    }
    y->right = x;
    y->parent = x->parent;
    x->parent = y;

    if(y->parent){
        if(y->parent->left && y->parent->left == x){
            y->parent->left = y;
        } else{
            y->parent->right = y;
        }
    }
}

template<typename T>
void Node<T>::rot_left(Node<T>* x){
    Node<T>* y = x->right;
    x->right = y->left;
    if(x->right){
        x->right->parent = x;
    }
    y->left = x;
    y->parent = x->parent;
    x->parent = y;

    if(y->parent){
        if(y->parent->left && y->parent->left == x){
            y->parent->left = y;
        } else{
            y->parent->right = y;
        }
    }
}

template<typename T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
    while (x->parent){
        if(x->parent == root){
            if(root->left && root->left == x){
                rot_right(root);
            } else{
                rot_left(root);
            }
        } else{
            Node<T>* p = x->parent;
            Node<T>* g = p->parent;
            if(g->left && p->left && g->left == p && p->left == x){
                rot_right(g);
                rot_right(p);
            } else if(g->right && p->right && g->right == p && p->right == x){
                rot_left(g);
                rot_left(p);
            } else if(g->right && p->left && g->right == p && p->left == x){
                rot_right(p);
                rot_left(g);
            } else if(g->left && p->right && g->left == p && p->right == x){
                rot_left(p);
                rot_right(g);
            }
        }
    }
    return x;
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
    aux << value;
    if (left != 0) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != 0) {
        aux << " ";
        right->preorder(aux);
    }
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
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

template <typename T>
class SplayTree {
private:
	Node<T> *root;

public:
	SplayTree();
	~SplayTree();
	bool empty() const;
	void add(T);
	bool find(T);
	void remove(T);
	void removeAll();
	std::string inorder() const;
	std::string preorder() const;
};

template <typename T>
SplayTree<T>::SplayTree() : root(nullptr) {}

template <typename T>
SplayTree<T>::~SplayTree(){
    removeAll();
}

template <typename T>
bool SplayTree<T>::empty() const{
    return (root == 0);
}

template <typename T>
void SplayTree<T>::add(T val){
    if(root != nullptr){
        Node<T>* added = root->add(val);
        root = root->splay(root, added);
    } else{
        root = new Node<T>(val);
    }
}

template <typename T>
bool SplayTree<T>::find(T val){
    if(!empty()){
        Node<T>* foundValue = root->find(val);
        root = root->splay(root, foundValue);
        return (root->value == val);
    }
    return 0;
}

template <typename T>
void SplayTree<T>::remove(T val){
    if(!empty()){
        if(root->value == val){
            Node<T>* succesorNode = root->succesor();
            if(succesorNode){
                succesorNode->left = root->left;
                succesorNode->right = root->right;
                if(succesorNode->left){
                    succesorNode->left->parent = succesorNode;
                }
                if(succesorNode->right){
                    succesorNode->right->parent = succesorNode;
                }
                succesorNode->parent = nullptr;
            }
            delete root;
            root = succesorNode;
        } else{
            Node<T>* p = root->remove(val);
            root = root->splay(root,p);
        }
    }
}

template <typename T>
void SplayTree<T>::removeAll(){
    if(!empty()){
        root->removeChilds();
        delete root;
    }
    root = nullptr;
}

template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}


#endif