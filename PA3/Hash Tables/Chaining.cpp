#ifndef CHAINING_CPP
#define CHAINING_CPP

#include "Chaining.h"
#include "HashFunction.cpp"


// Constructor
HashC::HashC(int size)
{
	tableSize = size ;

	shared_ptr<LinkedList<string>> ptr(new LinkedList<string>[tableSize], default_delete<LinkedList<string>[]>());
	hashTable = ptr;
	LinkedList<string> list;

	for(int i = 0; i < tableSize; i++)
	{
		hashTable.get()[i] = list;
	}

}


// Destructor
HashC::~HashC()
{
    hashTable.reset() ;
    hashTable = NULL ;
	
}


// Given a String, return its hash
unsigned long HashC::hash(string input)
{
    return divCompression( bitHash(input), tableSize )  ;
	
}


// Takes a hash of 'word' and inserts it into hashTable accordingly
void HashC::insertWord(string word)
{
    unsigned long hashKey = hash(word) ;
    LinkedList<string> tempList = hashTable.get()[hashKey]; 

    tempList.insertAtTail(word) ;

}


// Locates 'word' in the hash table and returns a pointer to it
shared_ptr<ListItem<string>> HashC::lookupWord(string word)
{
    unsigned long hashKey = hash(word) ;
    LinkedList<string> tempList = hashTable.get()[hashKey];
    return tempList.searchFor(word) ;
}


// Deletes 'word' from the hash table
void HashC::deleteWord(string word)
{
    unsigned long hashKey = hash(word) ;
    LinkedList<string> tempList = hashTable.get()[hashKey];
    tempList.deleteElement(word) ;

}


#endif