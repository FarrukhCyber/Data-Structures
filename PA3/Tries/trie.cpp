#ifndef __TRIE_CPP
#define __TRIE_CPP

#include "trie.hpp"
#include <cstring>
#include <bits/stdc++.h>
#include <string>


trie::trie()
{
    root = shared_ptr<Node>(new Node); root->value = ' ';
}

void trie::insertWord(string word)
{
    // coverting string into a char array----------
    int len = word.size() ;
    char str[len+1] ;
    strcpy(str, word.c_str()) ;
    //---------------------------------------------

    shared_ptr<Node> node = this->root ;

    for (int i = 0; i < len; i++)
    {
        int index = findChar(node, str[i]);

        // that character isn't the child
        if (index == -1)
        {
            // make a new node and set its value
            shared_ptr<Node> newNode(new Node);
            newNode->value = str[i] ;
            node->children.push_back(newNode) ;
            sort(node->children) ;

            node = newNode ;
        }
        else{
            node = node->children[index] ;
        }
    }
        
}

bool trie::search(string word)
{
    // coverting string into a char array----------
    int len = word.size() ;
    char str[len+1] ;
    strcpy(str, word.c_str()) ;
    //---------------------------------------------

    shared_ptr<Node> node = this->root ;
    int count = 0 ;

    for (int i = 0; i < len; i++)
    {
        for (int k = 0; k < node->children.size(); k++)
        {
            if (node->children[k]->value == str[i])
            {
                node = node->children[k] ;
                count++ ;
                break ;
            }   
        } 
    }

    if (count == len)
    {
        return true ;
    }
    else return false ;

}

string trie::longestSubstr(string word)
{
    // coverting string into a char array----------
    int len = word.size() ;
    char str[len+1] ;
    strcpy(str, word.c_str()) ;
    //---------------------------------------------

    shared_ptr<Node> node = this->root ;
    string result = "" ;
    string s ;
    bool flag = true ;

    for (int i = 0; i < len; i++)
    {
        for (int k = 0; k < node->children.size(); k++)
        {
            if (node->children[k]->value == str[i])
            {
                node = node->children[k] ;
                // convert to string
                string s(1, str[i]) ;
                result+= s ;
                flag = false ;
                break ;
            }
            else flag = true ;

        }

        if (flag)
        {
            break ;
        }
        
    }

    return result;

}

vector<string> getTrieHelper(shared_ptr<Node> node)
{
    vector<string> v ;
    //if we are at last node
    if (node->children.empty())
    {
    	char c = node->value;
        string s(1, c) ;
        if(node->value!=' ')
        {
        	//just puts the value of node in vector and returns it 
	        v.push_back(s) ;
        }

        return v;
    }
    //if we are not at the last node
    for (int i = 0; i < node->children.size(); i++)
    {
    	vector<string> temp ;
    	//gets all the possible strings from all the children
	    temp = getTrieHelper(node->children[i]) ;
	    //concatenates this node's value before all the words that we got from children
	    //and stores them inn vector v
	    for(int k=0; k<temp.size(); k++)
	    {
	    	if(node->value!=' ')
            {
	    		//concatenating nodes value with all the children words
	    		v.push_back(node->value+temp[k]);
            }
	    	else
	    		v.push_back(temp[k]);
	    }
    }

    return v;
}

vector<string> trie::getTrie()
{
    vector<string> v ;
    v = getTrieHelper(root) ;
    return v ;
}

void trie:: deleteHelper(string word)
{
    if (word.size() == 0)
    {
        return ;
    }
    
   // coverting string into a char array----------
    int len = word.size() ;
    char str[len+1] ;
    strcpy(str, word.c_str()) ;
    //---------------------------------------------

    shared_ptr<Node> node = root ;
    shared_ptr<Node> prev = node ;

    // move to the end of the word
    int i = 0 ;
   for (i = 0; i < len; i++)
    {
        for (int k = 0; k < node->children.size(); k++)
        {
            if (node->children[k]->value == str[i])
            {
                prev = node ;
                node = node->children[k] ;
                break ;
            }   
        } 
    }

    int pos = findChar(prev, str[i-1]) ;

    if(pos == -1)
    {
        return ;
    }

    if (prev->children[pos]->children.empty() == false)
    {
        return ;
    }
    

    for (int k = pos+1; k < prev->children.size(); k++)
    {
        prev->children[k-1] = prev->children[k] ;
    }
    prev->children.pop_back() ;

    word.pop_back();
    deleteHelper(word) ;
}

void trie::deleteWord(string word)
{
    if (search(word) == false)
    {
        return ;
    }

   deleteHelper(word) ;
    
    
}

// ------------Helper functions--------------------
int trie:: findChar(shared_ptr<Node> parent, char toFind)
{
    for (int i = 0; i < parent->children.size(); i++)
    {
        if(parent->children[i]->value == toFind)
        {
            return i ;
        }
    }
    
    return -1 ;
}

void trie:: sort(vector<shared_ptr<Node>> &nums)
{
    // insertion sort
    int size = nums.size() ;
    shared_ptr<Node> arr[size] ;
    shared_ptr<Node> item ;
    
    for (int i = 0; i < size; i++)
    {
        arr[i] = nums[i] ;

        int curr = i ;
        while (curr > 0 && arr[curr]->value < arr[curr-1]->value)
        {
            // do the swapping
            shared_ptr<Node> temp = arr[curr] ;
            arr[curr] = arr[curr-1] ;
            arr[curr-1] = temp ;

            --curr ; 
        }  
    }

    // transfering back the elements
    for (int i = 0; i <size; i++)
    {
        nums[i] = arr[i] ;
    }

}

   


#endif