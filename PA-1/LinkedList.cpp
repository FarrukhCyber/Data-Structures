#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include <memory>
#include "LinkedList.h"
using namespace std;

template <class T>
LinkedList<T>::LinkedList()
{
    head = NULL ;
    tail = NULL ;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList) 
{

    shared_ptr<ListItem<T>> iterate = otherLinkedList.head ;
    shared_ptr<ListItem<T>> node ;
	shared_ptr<ListItem<T>> curr_node = otherLinkedList.head ;
	shared_ptr<ListItem<T>> prev_node  ; 
	head = NULL;
	tail = NULL;
    int i=0 ;

	while(iterate != NULL){

		shared_ptr<ListItem<T>> node(new ListItem<T>(NULL)) ;
		node->value = curr_node->value;
		node->prev = prev_node;
		node->next = NULL;
		if (i == 0) {
			head = node;
            i++ ;
		}
		else {
			prev_node->next = node;
		}
		curr_node = curr_node->next;
		prev_node = node;
        iterate = iterate->next ; // loop iterator
	}
	tail = node;
   
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
    
    shared_ptr<ListItem<T>> newNode(new ListItem<T>(item)) ;
    if (head == NULL)
    {
        head = newNode ;
        tail = newNode ;
    }
    else
    {
        newNode->next = head ;
        head->prev = newNode ;
        this->head = newNode ;

    }
    
    
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
    shared_ptr<ListItem<T>> newNode(new ListItem<T>(item)) ;

    if (head == NULL)
    {
        head = newNode ;
        tail = newNode ;
    }
    else
    {
        newNode->next = NULL ;
        newNode->prev = tail ;
        tail->next = newNode ;
        tail = newNode ;

    }

    
    
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
    if (this->head == NULL)
    {
        return ;
    }
    
    shared_ptr<ListItem<T>> key = searchFor(afterWhat)  ;

    // afterwhat is not present
    if (key == NULL)
    {
        return ;
    }
    
    shared_ptr<ListItem<T>> newNode(new ListItem<T>(toInsert)) ;

    // if afterwhat is at the end, then we have to do insertion at the end
    if (key->next == NULL)
    {
        key->next = newNode ;
        newNode->prev = key ;
    }

    // in between insertion
    else
    {
      newNode->next = key->next ;
      key->next->prev = newNode ;
      newNode->prev = key ;
      key->next = newNode ;
    }

}


template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::getHead()
{
    return head ;
}

template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::getTail()
{
    return tail ;
}

template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::searchFor(T item)
{
    if (this->head == NULL)
    {
        return NULL ;
    }

    shared_ptr<ListItem<T>> newNode(new ListItem<T>(item)) ;
    newNode = this->head ;

    while (newNode != NULL)
    {
        if(newNode->value == item)
        {
            return newNode ;
        }
        else
        {
            newNode = newNode->next ;
        }
    }

    return NULL ;
    
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
    // list is empty
    if (this->head == NULL) 
    {
        return ;
    }
    
    shared_ptr<ListItem<T>> key(new ListItem<T>(item)) ;
    key = searchFor(item) ;

    // required value is not in the list
    if (key == NULL) 
    {
        return ;
    }

    // value is at the head node
    if (head->value == item)
    {
        deleteHead() ;
    }

    // if the value is at the tail
    else if (tail->value == item)
    {
        deleteTail() ;
    }

    // in between value
    else
    {
        key->prev->next = key->next ;
        key->next->prev = key->prev ;
        key->next = NULL ;
        key->prev = NULL ;
    }
    
}

template <class T>
void LinkedList<T>::deleteHead()
{
    // empty list
    if (this->head == NULL)
    {
        return ;
    }

    // single node in the list
    if (head->next == NULL)
    {
        head = NULL ;
        tail = NULL ;
    }

    // for more than one nodes
    else
    {
        head = head->next ;
        head->prev->next = NULL ;
        head->prev = NULL ;

    }

}

template <class T>
void LinkedList<T>::deleteTail()
{
    // empty list
    if (head == NULL)
    {
        return ;
    }

    // single node in the list

    if (head == tail)
    {
        head = NULL ;
        tail = NULL ;
        // return ;
    }

    
    // for more than one nodes
    else
    {
        tail = tail->prev;
        tail->next->prev = NULL ;
        tail->next = NULL;
    }

}

template <class T>
int LinkedList<T>::length()
{
    // if the list empty
    if (head == NULL)
    {
        return 0 ;
    }

    shared_ptr<ListItem<T>> temp = head;

    // temp = head ;
    int count=0 ;

    while (temp!=NULL)
    {
        temp = temp->next ;
        count++ ;
    }

    return count ;

}

#endif
