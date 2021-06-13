#ifndef BurgerJoint_CPP
#define BurgerJoint_CPP
#include "BurgerJoint.h"
#include <fstream>

/*
    Helper function to tell whether the 
    given string is a number or not 
*/
bool isNumber(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if( !(isdigit((unsigned char)str[i])) )
        {
            return false;
        }
        
    }

    return true;
}


/*
    Constructor:
    1. Load topping priority from topping_priority.txt into
       topping_priority attribute
    2. Load every customers' unsorted toppings form 
       assembly line - load data from assembly.txt 
       into customers queue
    
    For you convenience this has been done!
*/
BurgerJoint::BurgerJoint()
{
   
    ifstream fin("topping_priority.txt");

    string line;

    int count = 0;

    while (getline (fin, line)) 
    {

        topping_priority[count] = line;
        count++;

    }

    //saving number of toppings
    number_of_toppings = count;

    fin.close();
    
    //loading customers' unsorted toppings from assembly line
    fin.open("assembly.txt");


    bool first_line = true;

    int total_customers;
    int cust_id;

    LinkedList<string> lines;

    //reading all lines
    while(getline (fin, line))
    {
        lines.insertAtTail(line);
    }

    fin.close();

    shared_ptr<ListItem<string>> ptr = lines.getHead();

    ptr = lines.getHead();

    //adding customers with correct id and toppings into
    //customers queue
    while(ptr != NULL)
    {
        line = ptr->value;
        if(first_line)
        {
            //noting down total customers
            total_customers = stoi(line);
            first_line = false;
            ptr = ptr -> next;
        }

        else
        {
            //noting down customer id
            cust_id = stoi(line);

            ptr = ptr->next;

            shared_ptr<customer> new_cust(new customer);
            new_cust->id = cust_id;

            //noting down customer unsorted toppings
            while(ptr != NULL)
            {  
                line = ptr->value;
                if(isNumber(ptr->value))
                {
                    break;
                }
                new_cust->order.push(line);
                ptr = ptr->next;
            }

            //enqueuing customer
            customers.enqueue(new_cust);
        }
        
    }

}


/*
    Function to fetch priority of a topping.
    Matches prioirity from topping_priority list.
*/
int BurgerJoint::getPriority(string item)
{
    int x=0 ;

    for (int i = 0; i < 10; i++)
    {
        if (topping_priority[i] == item)
        {
            x= i+1 ;
        }
    }

    return x ;


}

//destructor
BurgerJoint::~BurgerJoint()
{}

/*
    You have two stacks:
    1. unsorted_toppings
    2. temp_stack

    You have one variable:
    1. temp

    DONOT CREATE ANYMORE VARIABLES OR DATASTRUCTURES IN THIS FUNCTION

    Use the above mentioned variable and datastructures to sort the
    unsorted_toppings stack.
    You need to sort it according to "topping_priority"
*/
void BurgerJoint::assemble(Stack<string> &unsorted_toppings)
{

    Stack<string> temp_stack ;
    
    string temp ;

   // tranfer the elements of temp_stack into input stack descending order
    while (unsorted_toppings.length())
    {
        // temp holds the minimum value
        temp = unsorted_toppings.pop() ;

        // if the element(s) in temp_stack is greater than temp then remove them
        while (temp_stack.length() && getPriority(temp) < getPriority(temp_stack.top()) )
        {
           unsorted_toppings.push(temp_stack.pop()) ; 
        }

        temp_stack.push(temp) ;
        
        
    }

   // tranfer the elements of input stack into temp_stack ascending order
    while (!temp_stack.isEmpty())
    {
        unsorted_toppings.push(temp_stack.pop()) ;
    }
    
    
}


/*
    Generate an output file similar to assembly.txt.
    The toppings need to be in a sorted order in this file.
    Moreover, every customer needs to hace the correct toppings.

    NAME THE OUTPUT TEXT FILE takeaway.txt
*/
void BurgerJoint::generateOutput()
{

    fstream file_name("takeaway.txt", ios:: out) ;
    file_name << customers.length()<< endl ;

    while (!customers.isEmpty())
    {
        shared_ptr<customer> ptr = customers.dequeue() ;
        file_name<< ptr->id <<endl ;
        while ( !ptr->order.isEmpty() )
        {
            file_name << ptr->order.pop() <<endl ;
        }
        
    }

    file_name.close() ;
    
    
}

void BurgerJoint::takeawayCounter()
{

    for (int i = 0; i < customers.length(); i++)
    {
        shared_ptr<customer> ptr = customers.dequeue() ;
        assemble( ptr->order ) ;
        customers.enqueue(ptr) ;
    }

    generateOutput() ;
    
    
}




#endif