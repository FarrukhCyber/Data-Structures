#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "LinkedList.cpp"

//===========================Helper Function Definition================================
shared_ptr<ListItem<long>> merge(shared_ptr<ListItem<long>> list1, shared_ptr<ListItem<long>> list2) ;
shared_ptr<ListItem<long>> partition(shared_ptr<ListItem<long>> head, int len);

//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
    int size = nums.size() ;
    long arr[size] ;
    long item ;
    
    for (int i = 0; i < size; i++)
    {
        arr[i] = nums[i] ;

        int curr = i ;
        while (curr > 0 && arr[curr] < arr[curr-1])
        {
            // do the swapping
            int temp = arr[curr] ;
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
    
    
    return nums ;
	
}

//=====================================================================================
vector<long> MergeSort(vector<long> nums)
{
    LinkedList<long> list ;

    //copying elements into a linked list
    for (int i = 0; i < nums.size(); i++)
    {
        list.insertAtTail(nums[i]) ;
    }

    int len = list.length() ;
    shared_ptr<ListItem<long>> mergedList = NULL ;


    mergedList = partition(list.getHead(), len) ;
    // mergedList = merge(list1, list2) ;

    // transfering the elements
    int i =0 ;
    while (mergedList)
    {
        nums[i] = mergedList->value ;
        mergedList = mergedList->next ;
        i++ ;
    }

    return nums ;
    
    
}

//=====================================================================================

//==============================Helper Functions=======================================

shared_ptr<ListItem<long>> partition(shared_ptr<ListItem<long>> head, int len)
{
    if (head->next == NULL)
    {
        return head ;
    }
    
    int l1 = len/2 ;
    int l2 = len - l1 ;

    shared_ptr<ListItem<long>> list1 = head ;
    shared_ptr<ListItem<long>> list2 = head ;
    shared_ptr<ListItem<long>> mergedList = NULL ;
    shared_ptr<ListItem<long>> temp = list1;

    for (int i = 0; i < l1; i++)
    {
        list2 = list2->next ;
    }
    list2->prev = NULL ;


    for (int i = 0; i < l1 -1; i++)
    {
        temp = temp->next ;
    }
    temp->next = NULL ;

    list1 = partition(list1, l1) ;
    list2 = partition(list2, l2) ;

    mergedList = merge(list1, list2) ;
    return mergedList ;
}


shared_ptr<ListItem<long>> merge(shared_ptr<ListItem<long>> list1, shared_ptr<ListItem<long>> list2)
{
    shared_ptr<ListItem<long>> finalList = NULL ;

    if (list1 == NULL)
    {
        return list2 ;
    }
    else if (list2  == NULL)
    {
        return list1 ;
    }

    if (list1->value <= list2->value)
    {
        finalList = list1 ;
        finalList->next = merge(list1->next, list2) ;
    }
    else
    {
        finalList = list2 ;
        finalList->next = merge(list1, list2->next) ;
    }

    return finalList ;

}


#endif