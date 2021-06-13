#ifndef LUCKYDRAW_CPP
#define LUCKYDRAW_CPP
#include "luckyDraw.h"
#include "stack.cpp"
#include "queue.cpp"
#include <iostream>


luckyDraw::luckyDraw(int count)
{
    totalCount = count ;
}

//populate lane_1 with the given array of winnersId   
void luckyDraw::populateQueue(int* winnersId)
{
    for (int i = 0; i < totalCount; i++)
    {
        lane_1.enqueue(winnersId[i]) ;
    }
    
}

//populate table_1 with the given array of giftsId   
void luckyDraw::populateTable(int* giftsId)
{
    for (int i = 0; i < totalCount; i++)
    {
        table_1.push(giftsId[i]) ;

    }

}

//reverse the queue keeping the conditions in mind
void luckyDraw::reverseQueue()
{
    for (int i = 0; i < totalCount; i++)
    {
        // moves back the front element to the end of queue
        for (int j = 0; j < lane_1.length()-1; j++)
        {
            lane_1.enqueue(lane_1.dequeue()) ;
        }

        // stores that last value in the new queue
        lane_2.enqueue(lane_1.dequeue()) ;
        
    }

    // copies the element from lane_2 to lane_1
    while (!lane_2.isEmpty())
    {
        lane_1.enqueue(lane_2.dequeue()) ;
    }
    
    
}

//transfer the stack keeping the conditions in mind
void luckyDraw::transferStack()
{
    for (int i = 0; i< totalCount-1 ; i++)
    {
        specialVariable = table_1.pop() ;

        //transfer remaining items to table_2
        for(int j=i ; j < totalCount-1 ; j++)
        {
            table_2.push(table_1.pop()) ;
        }

        // transfer back the top element of table_1
        table_1.push(specialVariable) ;

        // transfer back the elements from table_2 to table_1
        for(int k=i ; k < totalCount-1 ; k++)
        {
            table_1.push(table_2.pop()) ;
        }
        
    }

    while (!table_1.isEmpty())
    {
        table_2.push(table_1.pop()) ;
    }

}



#endif
