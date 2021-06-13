#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"
#include <memory>

MinHeap::MinHeap(int cap)
{
	capacity = cap ;
	heap_size = 0 ;
	harr.reset(new int[capacity], default_delete<int[]>());
}
 
int MinHeap::parent(int i)
{
	return (i-1)/2 ;
}
 
int MinHeap::left(int i)
{
	return (2*i + 1) ;
}
 
int MinHeap::right(int i)
{
	return (2*i + 2) ;
}
 
int MinHeap::extractMin()
{
	// replacement
	int i = 0 ;
	int min = harr.get()[0] ;
	harr.get()[i] = harr.get()[heap_size-1] ;
	--heap_size ;
	int smallest ;

	while (1)
	{
		int l = left(i) ;
		int r = right(i) ;


		// finding the smallest child
		if (l < heap_size && harr.get()[l] < harr.get()[r])
		{
			smallest = l ;
		}
		else if(r < heap_size && harr.get()[r] < harr.get()[l])
		{
			smallest = r ;
		}
		else break ;
	
		// swapping
		if (smallest < heap_size && harr.get()[smallest] < harr.get()[i])
		{
			int temp = harr.get()[smallest] ;
			harr.get()[smallest] = harr.get()[i] ;
			harr.get()[i] = temp ;

			i = smallest ;
		}
		else break ;
	}

	return min ;

	
}
 
void MinHeap::decreaseKey(int i, int new_val)
{
	harr.get()[i] = new_val ;

	// heapifying if the heap property is disturbed
	while (1)
	{
		int p = parent(i) ;
		if (p >=0 && harr.get()[p] > harr.get()[i])
		{
			int temp = harr.get()[p] ;
			harr.get()[p] = harr.get()[i] ;
			harr.get()[i] = temp ;

			i = p ;
			
		}
		else break ;	
	}
}
 
int MinHeap::getMin()
{
	return harr.get()[0] ;
	
}
 
void MinHeap::deleteKey(int i)
{
	if (i >= heap_size)
	{
		return ;
	}
	
	// replacement
	harr.get()[i] = harr.get()[heap_size-1] ;
	--heap_size ;
	int smallest ;

	while (1)
	{
		int l = left(i) ;
		int r = right(i) ;


		// finding the smallest child
		if (l < heap_size && harr.get()[l] < harr.get()[r])
		{
			smallest = l ;
		}
		else if(r < heap_size && harr.get()[r] < harr.get()[l])
		{
			smallest = r ;
		}
		else break ;
	
		// swapping
		// for handling leaf nodes
		if (smallest < heap_size && harr.get()[smallest] < harr.get()[i])
		{
			int temp = harr.get()[smallest] ;
			harr.get()[smallest] = harr.get()[i] ;
			harr.get()[i] = temp ;

			i = smallest ;
		}
		else break ;

	}

			
}
 
void MinHeap::insertKey(int k)
{
	// heap is full
	if (heap_size == capacity)
	{
		return ;
	}


	harr.get()[heap_size] = k ;
	heap_size++ ;

	int c = heap_size -1 ;
	int par = (c-1)/2 ; 

	while (c > 0)
	{
		if (harr.get()[c] < harr.get()[par] )
		{
			// swap child with the parent
			int temp = harr.get()[c] ;
			harr.get()[c] = harr.get()[par] ;
			harr.get()[par] = temp ;

			// update parent and child
			c = par ;
			par = (c-1)/2 ;
		}
		else break ;	
	}
		
}

shared_ptr<int> MinHeap::getHeap()
{
	return harr;
}

#endif