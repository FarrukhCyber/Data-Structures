#ifndef __TREE_CPP
#define __TREE_CPP

#include "tree.hpp"


// Constructor
template <class T, class S>
Tree<T,S>::Tree(shared_ptr<node<T,S>> root) {
	this->root = root;
}

// This function finds a key in the tree and returns the respective node
template <class T, class S>
shared_ptr<node<T,S>> Tree<T,S>::findKey(T key) {
	return findKeyHelper(root,key);
}

// Helper function to find a key in the tree
template <class T, class S>
shared_ptr<node<T,S>> Tree<T,S>::findKeyHelper(shared_ptr<node<T,S>> currNode, T key) {
	
	if(currNode == NULL){
		return NULL ;
	}

	else if (currNode->key == key)
	{
		return currNode ;
	}

	else if(currNode->sibling != NULL)
	{
		shared_ptr<node<T,S>> temp = currNode->sibling ;
		shared_ptr<node<T,S>> exist = NULL ;

		while (temp != NULL)
		{
			exist = findKeyHelper(temp, key) ;
			if(exist != NULL)
			{
				return exist ;
			}
			
			temp = temp->child ;
		} 
		
	}

	return findKeyHelper(currNode->child, key)  ;

}

// This function inserts a the given node as a child of the given key
template <class T, class S>
bool Tree<T,S>::insertChild(shared_ptr<node<T,S>> c, T key) {

	shared_ptr<node<T,S>> parent = findKey(key) ;
	// case-1: key doesn't exist
	if(parent == NULL)
	{
		return false ;
	}

	//case-2: duplicate keys
	shared_ptr<node<T,S>> dup = findKey(c->key) ;
	if(dup){
		return false ;
	}

	// Case-3: key exist
	shared_ptr<node<T,S>> prev ;
	shared_ptr<node<T,S>> temp = parent->child ;

	if (parent->child == NULL)
	{
		parent->child = c ;
	}
	else
	{
		while (temp != NULL)
		{
			prev = temp ;
			temp = temp->sibling ;
		}

		prev->sibling = c ;
		
	}

	return true ;
	
}

// This function returns all the children of a node with the given key
template <class T, class S>
vector<shared_ptr<node<T,S>> > Tree<T,S>::getAllChildren(T key) {

	shared_ptr<node<T,S>> parent = findKey(key) ;
	vector<shared_ptr<node<T,S>>> vec ;

	//case-1: key doesn't exist
	if(parent == NULL){
		return vec;
	}

	// Case-2: node doesn't have children
	else if(parent->child == NULL){
		return vec ;
	}


	//Case-3: Node have children
	else
	{
		shared_ptr<node<T,S>> temp = parent->child ;

		for (int i = 0; temp; i++)
		{
			vec.push_back(temp) ;
			temp = temp->sibling ;

		}
	
	}
	
	return vec ;

}

// This function returns the height of the tree
template <class T, class S>
int Tree<T,S>::findHeight() {
	return findHeightHelper(root);
	// return 0 ;
}

// Helper function to find height of the tree
template <class T, class S>
int Tree<T,S>::findHeightHelper(shared_ptr<node<T,S>> currNode) {

	int h =0 ;
	int maxh =0 ;

	shared_ptr<node<T,S>> rootChild = root->child ;
	currNode = rootChild ;

	while (rootChild != NULL)
	{
		while (currNode != NULL)
		{
			currNode = currNode->child ;
			h++ ;
		}

		if(h > maxh)
		{
			maxh = h ;
			h=0 ;
		}

		rootChild = rootChild->sibling ;
		if(rootChild){
			currNode = rootChild->child ;
		}
		
		
	}

	return maxh ;
		
}

// This function deletes the node of a given key (iff it is a leaf node)
template <class T, class S>
bool Tree<T,S>::deleteLeaf(T key) {

	// deleting the root node
	if(root->key == key)
	{
		return false ;
	}

	if(deleteLeafHelper(root, key))
	{
		return true ;
	}
	else{
		return false ;
	}

}

// Helper function to delete lead node
template <class T, class S>
shared_ptr<node<T,S>> Tree<T,S>::deleteLeafHelper(shared_ptr<node<T,S>> currNode, T key) {

	shared_ptr<node<T,S>> leaf = findKey(key) ;
	shared_ptr<node<T,S>> prev= getPrev(currNode, key) ;
	bool isChild ;

	// to check whether the leaf node is the child of prev node or not
	if(prev->child == leaf)
	{
		isChild = true ;
	}
	else isChild = false ;

	// Case-1: leaf node
	if(leaf->child == NULL)
	{
		if(leaf->sibling == NULL)
		{
			if(isChild)
			{
				prev->child = NULL ;
			}
			else prev->sibling = NULL ;
		}
		else
		{
			if(isChild)
			{
				prev->child = leaf->sibling ;
			}
			else prev->sibling = leaf->sibling ;
		}

		return currNode ;
	}
	else
	{
		return NULL ;
	}
}

// This function deletes the tree
template <class T, class S>
void Tree<T,S>::deleteTree(shared_ptr<node<T,S>> currNode) {
	root = NULL ;
	return;
}

// This function returns the root of the tree
template <class T, class S>
shared_ptr<node<T,S>>  Tree<T,S>::getRoot() {
	return root;
}

// This function returns the previous pointer of the given key
template <class T, class S>
shared_ptr<node<T,S>>  Tree<T,S>::getPrev(shared_ptr<node<T,S>> currNode,T key)
{
	if(currNode == NULL){
		return NULL ;
	}

	else if (currNode->child != NULL && currNode->child->key == key )
	{
		// cout<< currNode->key<<endl ;
		return currNode ;
	}

	else if (currNode->sibling != NULL && currNode->sibling->key == key )
	{
		// cout<< currNode->key<<endl ;
		return currNode ;
	}


	else if(currNode->child != NULL)
	{
		shared_ptr<node<T,S>> temp = currNode->child;
		shared_ptr<node<T,S>> exist = NULL ;

		while (temp != NULL)
		{
			exist = getPrev(temp, key) ;
			if(exist != NULL)
			{
				return exist ;
			}
			
			temp = temp->sibling ;
		} 
		
	}

	return NULL ;

	// return findKeyHelper(currNode->child, key)  ;
}



#endif