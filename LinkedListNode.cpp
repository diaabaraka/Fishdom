#include "LinkedListNode.h"
#include <iostream>


LinkedListNode::LinkedListNode(int cellContents1,int elapsedTime1 ,int size1,LinkedListNode*next1,
                               LinkedListNode*prev1)
{
    cellContents=cellContents1;
    elapsedTime=elapsedTime1;
    size=size1;
    next=next1;
    prev=prev1;
}
LinkedListNode::~LinkedListNode()
{
}
void LinkedListNode::setCellContents(int cellContents1)
{
    cellContents=cellContents1;

}
void LinkedListNode:: setElapsedTime(int elapsedTime1)
{
    elapsedTime=elapsedTime1;


}
void   LinkedListNode:: setSize(int size1)
{
    size=size1;


}
void LinkedListNode:: setNext(LinkedListNode *next1)
{
    next=next1;


}
void LinkedListNode:: setPrev(LinkedListNode *prev1)
{
    prev=prev1;

}
int LinkedListNode::  getCellContents()
{

    return cellContents;

}
int LinkedListNode:: getElapsedTime()
{
    return elapsedTime;
}
int LinkedListNode:: getSize()
{
    return size;

}
LinkedListNode * LinkedListNode::  getNext()
{

    return next;
}
LinkedListNode * LinkedListNode:: getPrev()
{
    return prev;
}

