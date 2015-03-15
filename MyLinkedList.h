#ifndef MYLINKEDLIST_H
#define MYLINKEDLIST_H
#include "LinkedListNode.h"


class MyLinkedList
{
public:
    MyLinkedList();
    ~MyLinkedList();
    void clear();
void remove();

    void add(int cellContents1,int elapsedTime1,int size1);
    void setHead(LinkedListNode *head1);
    void setTail(LinkedListNode *tail1);
    LinkedListNode*getHead();
    LinkedListNode*getTail();
    int getSize();
private:
    LinkedListNode*head;
    LinkedListNode*tail;
    int sizer;
};

#endif // MYLINKEDLIST_H
