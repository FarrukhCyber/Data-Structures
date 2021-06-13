#include "avl.cpp"
#include <memory>
#include <cstdlib>
using namespace std;

#ifndef __AVL_HPP
#define __AVL_HPP

// Node of the tree
template <class T, class S>
struct node{
    T key;
    S value; 
    shared_ptr<node> left;
    shared_ptr<node> right;
    int height;
    
    node(T key, S value){
        this->key = key;
        this->value = value;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

// AVL Class (This will be used for both BST and AVL Tree implementation)
template <class T, class S>
class AVL {
    shared_ptr<node<T,S>> root;
    bool isAVL;
    
public:
    AVL(bool);
    void insertNode(shared_ptr<node<T,S>> newNode);
    void deleteNode(T k);    
    shared_ptr<node<T,S>> searchNode(T k);
    shared_ptr<node<T,S>> getRoot();
    int height (shared_ptr <node<T,S>> p);

    // Helper functions
    shared_ptr<node<T,S>> getParent(T k);
    shared_ptr<node<T,S>> getMin(shared_ptr<node<T,S>> newNode);
    shared_ptr<node<T,S>> insertHelper(shared_ptr<node<T,S>> rootNode, shared_ptr<node<T,S>> newNode);
    //helper functions for AVL part
    int isBalanced(shared_ptr<node<T,S>> node) ;
    shared_ptr<node<T,S>> insertAVL(shared_ptr<node<T,S>> node, T k);
    shared_ptr<node<T,S>> rotateRight(shared_ptr<node<T,S>> oldroot);
    shared_ptr<node<T,S>> rotateLeft(shared_ptr<node<T,S>> oldroot);


    
};


#endif