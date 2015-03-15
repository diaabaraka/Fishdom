#include "MyLinkedList.h"
#include <iostream>


MyLinkedList::MyLinkedList()
{
    head=NULL;
    tail=NULL;
    sizer=0;
}

MyLinkedList::~MyLinkedList()
{
    clear();
}
void MyLinkedList::clear()
{

    while(head!=NULL)
    {
       remove();
    }

}
void MyLinkedList::remove()
{
    LinkedListNode* p = head;

    head=head->getNext();
    head->setPrev(NULL);
    p=NULL;
    delete(p);
    sizer--;


}














void MyLinkedList::add(int cellContents1,int elapsedTime1 ,int size1)
{

    if(tail!=NULL)
    {
        LinkedListNode* newnode = new LinkedListNode(cellContents1,elapsedTime1,size1,0,tail);
        tail->setNext(newnode);
        tail=newnode;



    }
    else
    {

        head=tail = new LinkedListNode(cellContents1,elapsedTime1,size1,0,0);



    }

    sizer++;

}


void MyLinkedList::setHead(LinkedListNode *head1)
{
    head=head1;

}
void MyLinkedList::setTail(LinkedListNode *tail1)
{

    tail=tail1;
}
LinkedListNode*MyLinkedList ::getHead()
{
    return head;

}
LinkedListNode*MyLinkedList::getTail()
{
    return tail;


}
int MyLinkedList ::getSize()
{

    return sizer;
}
