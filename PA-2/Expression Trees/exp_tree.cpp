#ifndef __EXP_TREE_CPP
#define __EXP_TREE_CPP

#include "exp_tree.hpp"
#include <bits/stdc++.h>
#include <cstring>

// class constructor that calls buildTree()
ExpTree::ExpTree(string postfix_exp, bool optimal) {
    buildTree(postfix_exp, optimal);
}

// optimal helper
shared_ptr<node> ExpTree::optimalHelper(shared_ptr<node> currNode)
{
    char rc = currNode->right->op ;
    char lc = currNode->left->op ;

    if ( (rc >=48 && rc<=57) && (lc >=48 && lc<=57) )
    {
        int ri = int(rc) -48 ;
        int li = int(lc) -48 ;

        int result = cal(li, ri, currNode) ;
        char ret = char(result) +48 ;

        shared_ptr<node> temp( new node(ret) ) ;
        return temp ;
    }

    return NULL ;   
    
}

double ExpTree::cal(double a , double b, shared_ptr<node> currNode)
{
    if (currNode->op == '+')
    {
        return a+b ;
    }
    if (currNode->op == '*')
    {
        return a*b ;
    }
    if (currNode->op == '-')
    {
        return a-b ;
    }
    if (currNode->op == '/')
    {
        return a/b ;
    }
    

}

// returns the constructed expression tree from the given postfix expression
// when the optimal argument is set, the subtrees not containing any variables are computed and their result is stored in the tree as only one node
void ExpTree::buildTree(string postfix_exp, bool optimal)
{
    // empty postfix expression
    if (postfix_exp == "")
    {
        root = NULL ;
        return ;
    }
    
    stack<shared_ptr<node>> s ;

    int len = postfix_exp.size() ;
    char str[len+1];
    strcpy(str, postfix_exp.c_str()) ;

    for (int i = 0; i < len; i++)
    {

        // substr is an opearator
        if (str[i] == '*' || str[i] == '+' || str[i] == '-' || str[i] == '/' )
        {
            shared_ptr<node> rootNode( new node(str[i]) );
            rootNode->right = s.top() ;
            s.pop() ;
            rootNode->left = s.top() ;
            s.pop() ;

            if (optimal)
            {
                shared_ptr<node> temp( new node('c') ) ;
                temp = optimalHelper(rootNode) ;

                // numeric value
                if (temp != NULL)
                {
                    s.push(temp) ;
                }
                else s.push(rootNode) ;
                
            }
            else
            {
                s.push(rootNode) ;
            }

           
        }
        // str is an operand
        else
        {
            shared_ptr<node> newNode(new node(str[i]));
            s.push(newNode) ;
        }    
    }
    
    root = s.top();
    // s.pop() ;
    return;
}

// returns the root node of the tree;
shared_ptr<node> ExpTree::getRoot()
{
    return root;
}

// returns the value of the expression given the value of the variables in the vector
double ExpTree::calculate(vector<Variable> variables)
{
    
	return calculateRecurse(root, variables);
}

// recursive function called by calculate():
double ExpTree::calculateRecurse(shared_ptr<node> currNode, vector<Variable> variables)
{
    if (currNode == NULL)
    {
        return -99 ;
    }

	if (currNode->op == '+' || currNode->op == '-' || currNode->op == '*' || currNode->op == '/')
    {
        double right = calculateRecurse(currNode->right, variables) ;
        double left = calculateRecurse(currNode->left, variables) ;

        return cal(left, right, currNode) ;
    }

    // numeric value
    else if ( currNode->op >=48 && currNode->op <=57 )
    {
        return (currNode->op - 48) ;
    }

    // variable
    else if (currNode->op >='a' && currNode->op <='z')
    {
        for (int i = 0; i < variables.size(); i++)
        {
            if (currNode->op == variables[i].name)
            {
                return variables[i].value ;
            }
        }
    }
    
}

// returns the infix expression with brackets added
string ExpTree::getInfix()
{
	return getInfixRecurse(root);
}

// recursive function called by getInfix():
string ExpTree::getInfixRecurse(shared_ptr<node> currNode)
{
 
    if(currNode == NULL){
        return "";
    }
    string s1 = getInfixRecurse(currNode->left);
    string s2 =  getInfixRecurse(currNode->right);
    
    if(currNode == root)
    {
        return s1 + currNode->op + s2;
    }


	if ( (currNode->op >= 42) && (currNode->op <= 47) )
    {
        return "(" + s1 + currNode->op + s2 + ")";
    }
    else
    {
        string s = "";
        s = s + currNode->op;  
        return s;
    }

}


#endif