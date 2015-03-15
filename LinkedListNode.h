#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H


class LinkedListNode
{
public:
    LinkedListNode(int cellContents1,int elapsedTime1 ,int size1,LinkedListNode*next1,
                   LinkedListNode*prev1);
    ~LinkedListNode();
    void setCellContents(int cellContents1);
    void setElapsedTime(int elapsedTime1);
    void setSize(int size);
    void setNext(LinkedListNode *next1);
    void setPrev(LinkedListNode *prev1);
    int getCellContents();
    int getElapsedTime();
    int getSize();
    LinkedListNode *getNext();
    LinkedListNode *getPrev();

private:

    int cellContents;
    int elapsedTime;
    int size;
    LinkedListNode *next;
    LinkedListNode *prev;
};

#endif // LINKEDLISTNODE_H
