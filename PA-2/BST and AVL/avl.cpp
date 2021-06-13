#ifndef __AVL_CPP
#define __AVL_CPP

#include <iostream>
#include <memory>
#include "avl.hpp"
#include <cstdlib>

// Constructor
template <class T, class S>
AVL<T,S>::AVL(bool isAVL){
	this->root = NULL;
    this->isAVL = isAVL;
}

//---------------------AVL helper functions--------------------------------------

template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S> :: rotateRight(shared_ptr<node<T,S>> oldroot)
{
    shared_ptr<node<T,S>> newroot = oldroot->left ;
    oldroot->left = newroot->right ;
    newroot->right = oldroot ;
    return newroot ;

}

template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S> :: rotateLeft(shared_ptr<node<T,S>> oldroot)
{
    shared_ptr<node<T,S>> newroot = oldroot->right ;
    oldroot->right = newroot->left ;
    newroot->left = oldroot ;

    return newroot ;

}

// This function tells whether a tree is balanced or not
template <class T, class S>
int AVL<T,S> :: isBalanced(shared_ptr<node<T,S>> node)
{
    int leftHeight = height(node->left) ;
    int rightHeight = height(node->right) ;

    return (leftHeight - rightHeight) ;
   
    
}


// this function balances the tree after insertion
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S> :: insertAVL(shared_ptr<node<T,S>> root, T k)
{
    // tree is balanced
    // if ((isBalanced(root) <= 1) && (isBalanced(root) >= -1) && (k >= -1) )
    
    
    // Left Left Case 
    if (isBalanced(root) > 1 && k < root->left->key) 
        return rotateRight(root); 

    // Right Right Case 
    else if (isBalanced(root) < -1 && k > root->right->key) 
        return rotateLeft(root); 

    // Left Right Case 
    else if (isBalanced(root) > 1 && k > root->left->key) 
    { 
        root->left = rotateLeft(root->left); 
        return rotateRight(root); 
    } 

    // Right Left Case 
    else if (isBalanced(root) < -1 && k < root->right->key) 
    { 
        root->right = rotateRight(root->right); 
        return rotateLeft(root); 
    }
    else{
        return root ;
    }

}


//------------------------------------------------------------------------
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S> :: insertHelper(shared_ptr<node<T,S>> rootNode, shared_ptr<node<T,S>> newNode)
{   
    // recursive method
    if (rootNode == NULL)
    {
        rootNode = newNode;
        return newNode ;
    }

    if (rootNode->key == newNode->key)
    {
        return rootNode ;
    }

    if (newNode->key > rootNode->key)
    {
        rootNode->right = insertHelper(rootNode->right, newNode) ;
    }
    else
    {
        rootNode->left = insertHelper(rootNode->left , newNode) ;
    }

    return rootNode;
}


// This function inserts a given node in the tree
template <class T, class S>
void AVL<T,S> :: insertNode(shared_ptr<node<T,S>> newNode){
    
    root = insertHelper(root, newNode) ;

    // AVL Insertion
    if (isAVL)
    {
       root = insertAVL(root, newNode->key) ;
    }
    return ;




}

template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S> :: getMin(shared_ptr<node<T,S>> node)
{

    while (node->left != NULL)
    {
        node = node->left ; 
    }
    return node;

}

// This function returns the parent of a node with given key
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S> :: getParent(T k){

    shared_ptr<node<T,S>> temp = root;
    shared_ptr<node<T,S>> parent = root;

    while (temp != NULL)
    {
        // parent found
        if (temp->key == k)
        {
            return parent;
        }

        // traversing right sub tree
        if (temp->key < k)
        {
            parent = temp ;
            temp = temp->right ;
        }

        // traversing left sub tree
        else
        {
            parent = temp ;
            temp = temp->left ;
        }
    }

    return NULL ;

}

// This function searches a node in a tree by its key
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S> :: searchNode(T k){

    shared_ptr<node<T,S>> temp = root;

    while (temp != NULL)
    {
        // key found
        if (temp->key == k)
        {
            return temp;
        }

        // traversing right sub tree
        if (temp->key < k)
        {
            temp = temp->right ;
        }

        // traversing left sub tree
        else
        {
            temp = temp->left ;
        }
    }

    return NULL ;
   
}

// This function deletes a given node from the tree
template <class T, class S>
void AVL<T,S>::deleteNode(T k){

    shared_ptr<node<T,S>> delNode = searchNode(k) ; // node to be deleted
    shared_ptr<node<T,S>> delNodeParent = getParent(k) ; // parent of that node
    shared_ptr<node<T,S>> temp ;

    // Case: leaf node
    if (delNode->left == NULL && delNode->right == NULL )
    {
        // delnode is the right child
        if (delNodeParent->right == delNode)
        {
            delNodeParent->right = NULL ;
        }
        // delNode is the left child
        else delNodeParent->left = NULL ; 

        return ;
    }

    // Case: Only One child
    if (delNode->left == NULL || delNode->right == NULL )
    {
        // delnode is the right child
        if (delNodeParent->right == delNode)
        {
            // delNode has only Right child
            if(delNode->right != NULL)
            {
                delNodeParent->right = delNode->right ;
            }

            // delNode has only Left child
            else
            {
                delNodeParent->right = delNode->left ;
            }

        }
        // delNode is the left child
        else 
        {
             // delNode has only Right child
            if(delNode->right != NULL)
            {
                delNodeParent->left = delNode->right ;
            }

            // delNode has only Left child
            else
            {
                delNodeParent->left = delNode->left ;
            }

        }

        return ;
    }

    // Case: Two children    
    if (delNode->left != NULL && delNode->right != NULL)
    {
        if (delNode->right->left == NULL)
        {
            delNode->key = delNode->right->key ;
            delNode->value = delNode->right->value ;
            temp = delNode->right->right ;
            delNode->right->right = NULL ;
            delNode->right = temp ;
        }
        else
        {
           shared_ptr<node<T,S>> minNode = getMin(delNode->right) ; 
           shared_ptr<node<T,S>> minParent = getParent(minNode->key) ;

           // copy min node contents
           delNode->key =  minNode->key ;
           delNode->value =  minNode->value ;

           // Case: minNode is a leaf node
           if (minNode->right == NULL)
           {
               minParent->left = NULL ;
           }
           // minNode has a right child
           else
           {
               temp = minNode->right ;
               minNode->right = NULL ;
               minParent->left = temp ;
           }
           
        }
        return ;
        
    }
    
}

// This function returns the root of the tree
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S>::getRoot(){
    return root;
}

// This function calculates and returns the height of the tree
template <class T, class S>
int AVL<T,S> :: height (shared_ptr<node<T,S>> p){

    int h ;
    if (p == NULL)
    {
        return 0;
    }
    
    if(p == NULL || (p->left == NULL && p->right == NULL)){
        return 1;
    }
            

	int leftHeight= height(p->left);
	int rightHeight = height(p->right);

	if(leftHeight > rightHeight){
        h = leftHeight + 1;
    }
	else h= rightHeight + 1;

    return h ;
    
}

#endif