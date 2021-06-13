#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "LinearProbing.h"
#include "HashFunction.cpp"
#include <memory>

// Constructor
HashL::HashL(int size)
{
    tableSize = size ;
    count = 0 ;

    for (int i=0; i<tableSize; i++)
    {
        hashTable.push_back(NULL);
    }
}

// Destructor
HashL::~HashL()
{
    hashTable.clear();
    count = 0;
}

// Computes the key corresponding to the value.
unsigned long HashL::hash(string value)
{
    return divCompression( bitHash(value), tableSize )  ;

}

// Function to resize the hash table
void HashL::resizeTable()
{
	if (count > tableSize*0.7)
    {
        tableSize*= 2;
        vector<shared_ptr<tableItem>> newTable ;
        newTable = hashTable ;

        // setting up the new table
        hashTable.clear();
        hashTable.resize(tableSize);

        // transfering back the contents
        for(int i=0 ; i<newTable.size(); i++)
        {
            if (newTable[i] != NULL)
            {
                insertWord(newTable[i]->value) ;
            }
        }
        newTable.clear() ;
    }
    
}

// Takes the hash of 'value' and insert it into the hash table
void HashL::insertWord(string value)
{
    unsigned long index = hash(value) ;
    resizeTable();
    // in case of single probing
    if (hashTable[index] == NULL)
    {
        shared_ptr<tableItem> temp(new tableItem (index, value));
        hashTable[index] = temp ;
        count++ ;
        return ;
    }
    // for more than one probing
    while (hashTable[index] != NULL)
    {
        index = (index+1)%tableSize;
    }
    shared_ptr<tableItem> temp(new tableItem (index, value));
    hashTable[index] = temp ;
    count++ ;

}


// Deletes 'value' from the hash table.
void HashL::deleteWord(string value)
{
	shared_ptr<tableItem> del = lookupWord(value);

    //value doesn't exist
    if (del == NULL)
    {
        return ;
    }

    //if the value exist
    del->value = "";
    del->key = 0;
    count--;


}

// Locates value in the hash table and returns a pointer to it
shared_ptr<tableItem> HashL::lookupWord(string value)
{
    int k = hash(value) ;

    for (int i = k; hashTable[i] != NULL; i = (i+1)%tableSize)
    {
        if (hashTable[i]->value == value)
        {
            return hashTable[i] ;
        } 
    }

    return NULL ;
	
}

#endif
