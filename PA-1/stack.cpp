#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{}
    
template <class T>
Stack<T>::Stack(Stack<T>& otherStack)
{
    shared_ptr<ListItem<T>> ptr = otherStack.list.getTail() ;

    while (ptr != NULL)
    {
        this->push(ptr->value) ;
        ptr = ptr->prev ;
    }

}

template <class T>
Stack<T>::~Stack()
{}

template <class T>
void Stack<T>::push(T item)
{
    list.insertAtHead(item) ;
}

template <class T>
T Stack<T>::top()
{
    shared_ptr<ListItem<T>> ptr = list.getHead() ;
    return ptr->value;
}

template <class T>
T Stack<T>::pop()
{
    shared_ptr<ListItem<T>> ptr = list.getHead() ; ;
    list.deleteHead() ;
    return ptr->value ;
}

template <class T>
int Stack<T>::length()
{
    int len = list.length() ;
    return len ;
}

template <class T>
bool Stack<T>::isEmpty()
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
