#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"
#include <iostream>

template <class T>
Queue<T>::Queue()
{}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue)
{
    shared_ptr<ListItem<T>> ptr = otherQueue.list.getHead() ;

    while (ptr != NULL)
    {
        this->enqueue(ptr->value) ;
        ptr = ptr->next ;
    }
    

}

template <class T>
Queue<T>::~Queue()
{}

template <class T>
void Queue<T>::enqueue(T item)
{
    if (list.getHead() == NULL)
    {
        list.insertAtHead(item) ;
        return ;
    }
    
    list.insertAtTail(item) ;
}

template <class T>
T Queue<T>::front()
{
    shared_ptr<ListItem<T>> ptr = list.getHead() ;
    return ptr->value;
}

template <class T>
T Queue<T>::dequeue()
{
    //if the queue is empty
    if (list.length() == 0)
    {
        return 0 ;
    }
    
    shared_ptr<ListItem<T>> ptr = list.getHead() ;
    list.deleteHead() ;

    return ptr->value ;
}

template <class T>
int Queue<T>::length()
{
    int len = list.length() ;
    return len ;
}

template <class T>
bool Queue<T>::isEmpty()
{
    int len = list.length() ;

    if (len == 0)
    {
        return true ;
    }
    else
    {
        return false ;
    }
}


#endif
