#include "RunLengthEncoding.h"
#include "Ocean.h"
#include "Cell.h"
#include "LinkedListNode.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
using namespace std;

/*
 *  The following methods are required for Part II.
 */

/*
 *  RunLengthEncoding() (with three parameters) is a constructor that creates
 *  a run-length encoding of an empty ocean having width i and height j,
 *  in which sharks starve after starveTime timesteps.
 *  @param i is the width of the ocean.
 *  @param j is the height of the ocean.
 *  @param starveTime is the number of timesteps sharks survive without food.
 */

RunLengthEncoding::RunLengthEncoding(int i, int j, int starveTime1)
{
    width=i;
    height=j;
    starveTime=starveTime1;
    list.add(Ocean::EMPTY,-1,width*height);
    pointerToRun=list.getHead();

}

/*
 *  RunLengthEncoding() (with five parameters) is a constructor that creates
 *  a run-length encoding of an ocean having width i and height j, in which
 *  sharks starve after starveTime timesteps.  The runs of the run-length
 *  encoding are taken from two input arrays.  Run i has length runLengths[i]
 *  and species runTypes[i].
 *  @param i is the width of the ocean.
 *  @param j is the height of the ocean.
 *  @param starveTime is the number of timesteps sharks survive without food.
 *  @param runTypes is an array that represents the species represented by
 *         each run.  Each element of runTypes is Ocean.EMPTY, Ocean.FISH,
 *         or Ocean.SHARK.  Any run of sharks is treated as a run of newborn
 *         sharks (which are equivalent to sharks that have just eaten).
 *  @param runLengths is an array that represents the length of each run.
 *         The sum of all elements of the runLengths array should be i * j.
 */

RunLengthEncoding::RunLengthEncoding(int i, int j, int starveTime1, int* runTypes, int runTypesSize, int* runLengths, int runLengthsSize)
{
    starveTime=starveTime1;
    width=i;
    height=j;
    for(int x=0; x<runTypesSize; x++)
    {
        if(runTypes[x]==Ocean::SHARK)
        {
            list.add(Ocean::SHARK,0,runLengths[x]);


        }
        else
        {
            list.add(runTypes[x],-1,runLengths[x]);



        }


    }
    pointerToRun=list.getHead();


}



// Destructor
RunLengthEncoding::~RunLengthEncoding()
{
    list.~MyLinkedList();
}


/*
 *  restartRuns() and nextRun() are two methods that work together to return
 *  all the runs in the run-length encoding, one by one.  Each time
 *  nextRun() is invoked, it returns a different run (represented as an
 *  array of two ints), until every run has been returned.  The first time
 *  nextRun() is invoked, it returns the first run in the encoding, which
 *  contains cell (0, 0).  After every run has been returned, nextRun()
 *  returns null, which lets the calling program know that there are no more
 *  runs in the encoding.
 *
 *  The restartRuns() method resets the enumeration, so that nextRun() will
 *  once again enumerate all the runs as if nextRun() were being invoked for
 *  the first time.
 *
 *  (Note:  Don't worry about what might happen if nextRun() is interleaved
 *  with addFish() or addShark(); it won't happen.)
 */

/*
 *  restartRuns() resets the enumeration as described above, so that
 *  nextRun() will enumerate all the runs from the beginning.
 */
void RunLengthEncoding::restartRuns()
{
    pointerToRun=list.getHead();
}

/*
 *  nextRun() returns the next run in the enumeration, as described above.
 *  If the runs have been exhausted, it returns null.  The return value is
 *  an array of two ints (constructed here), representing the type and the
 *  size of the run, in that order.
 *  @return the next run in the enumeration, represented by an array of
 *          two ints.  The int at index zero indicates the run type
 *          (Ocean.EMPTY, Ocean.SHARK, or Ocean.FISH).  The int at index one
 *          indicates the run length (which must be at least 1).
 */

void RunLengthEncoding::nextRun(int* result, int* size)
{
    if(pointerToRun==NULL)
    {
        *size=0;
    }
    else
    {
        *result=pointerToRun->getCellContents();
        *size=pointerToRun->getSize();
        pointerToRun=pointerToRun->getNext();

    }



}

/*
 *  toOcean() converts a run-length encoding of an ocean into an Ocean
 *  object.  You will need to implement the three-parameter addShark method
 *  in the Ocean class for this method's use.
 *  @return the Ocean represented by a run-length encoding.
 */

Ocean* RunLengthEncoding::toOcean()
{
    Ocean *sea=new Ocean (width, height, starveTime);
    int rowCount=0;
    int colCount=0;
    LinkedListNode *p=list.getHead();
    while(p!=NULL)
    {
        int length=p->getSize();
        for(int x=0; x<length; x++)
        {

            if(p->getCellContents()==Ocean::FISH)
            {
                sea->addFish(colCount,rowCount);

            }
            else if(p->getCellContents()==Ocean::SHARK)
            {
                sea->addShark(colCount,rowCount,p->getElapsedTime());

            }

            colCount++;

            if(colCount==width)
            {
                rowCount++;

                colCount=0;
//                if(rowCount==height){
//                    x=length;
//                }

            }



        }






        p=p->getNext();

    }

    return sea;
}

/*
 *  The following method is required for Part III.
 */

/*
 *  RunLengthEncoding() (with one parameter) is a constructor that creates
 *  a run-length encoding of an input Ocean.  You will need to implement
 *  the sharkFeeding method in the Ocean class for this constructor's use.
 *  @param sea is the ocean to encode.
 */

RunLengthEncoding::RunLengthEncoding(Ocean sea)

{
    width=sea.width();
    height=sea.height();
    starveTime=sea.starveTime();
    int count=0;
    int type=sea.cellContents(0,0);
    int elapsedTime1=sea.sharkFeeding(0,0);
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            if(type==sea.cellContents(j,i)&&elapsedTime1==sea.sharkFeeding(j,i))
            {
                count++;
            }
            else
            {
                list.add(type,elapsedTime1,count);
                type=sea.cellContents(j,i);
                elapsedTime1=sea.sharkFeeding(j,i);
                count=1;


            }






        }
    }
    list.add(type,elapsedTime1,count);
    pointerToRun=list.getHead();
    check();
}

/*
 *  The following methods are required for Part IV.
 */

/*
 *  addFish() places a fish in cell (x, y) if the cell is empty.  If the
 *  cell is already occupied, leave the cell as it is.  The final run-length
 *  encoding should be compressed as much as possible; there should not be
 *  two consecutive runs of sharks with the same degree of hunger.
 *  @param x is the x-coordinate of the cell to place a fish in.
 *  @param y is the y-coordinate of the cell to place a fish in.
 */
int RunLengthEncoding::doWarpping(int coordinate,int maxCoordinate)
{

    int x=coordinate%maxCoordinate;
    if(x>=0)
    {
        return x;
    }
    return (x+maxCoordinate);

}

void RunLengthEncoding::addFish(int x, int y)
{

    int indexOfNode=(width*doWarpping(y,height))+doWarpping(x,width)+1;
    LinkedListNode * p1=list.getHead();
    if(indexOfNode==1)
    {
        if(p1->getCellContents()==Ocean::EMPTY)
        {
            if(p1->getSize()==1)
            {
                if(p1->getNext()->getCellContents()==Ocean::FISH)
                {

                    p1->getNext()->setSize(p1->getNext()->getSize()+1);
                    list.setHead(p1->getNext());
                    list.getHead()->setPrev(0);
                    delete  p1;
                }
                else
                {
                    p1->setCellContents(Ocean::FISH);
                }

            }
            else
            {
                LinkedListNode* newnode = new LinkedListNode(Ocean::FISH,-1,1,p1,0);
                p1->setPrev(newnode);
                p1->setSize( p1->getSize()-1);
                list.setHead(newnode);

            }


        }
    }
    else if(indexOfNode==width*height)
    {
        if(list.getTail()->getCellContents()==Ocean::EMPTY)
        {
            if(list.getTail()->getSize()==1)
            {

                if(list.getTail()->getPrev()->getCellContents()==Ocean::FISH)
                {
                    LinkedListNode*q=list.getTail();

                    list.getTail()->getPrev()->setSize(list.getTail()->getPrev()->getSize()+1);
                    list.setTail(list.getTail()->getPrev());
                    list.getTail()->setNext(0);
                    delete  q;
                }
                else
                {
                    list.getTail()->setCellContents(Ocean::FISH);
                }
            }
            else
            {
                LinkedListNode* newnode = new LinkedListNode(Ocean::FISH,-1,1,0,list.getTail());
                list.getTail()->setNext(newnode);
                list.getTail()->setSize(list.getTail()->getSize()-1);
                list.setTail(newnode);


            }


        }
    }
    else
    {

        int postion=0;
        LinkedListNode * p=list.getHead();
        int i=1;
        while(p!=NULL&&i>0)
        {
            postion+=p->getSize();

            if(indexOfNode<=postion)
            {
                if(p->getCellContents()==Ocean::EMPTY)
                {
                    if(p->getSize()==1)
                    {
                        if(p->getNext()->getCellContents()==Ocean::FISH&&p->getPrev()->getCellContents()==Ocean::FISH)
                        {

                            p->getPrev()->setSize(p->getPrev()->getSize()+1+p->getNext()->getSize());
                            p->getPrev()->setNext(p->getNext()->getNext());
                            p->getNext()->getNext()->setPrev(p->getPrev());
                            delete p->getNext();
                            delete p;


                        }
                        else if (p->getNext()->getCellContents()==Ocean::FISH)
                        {
                            p->getNext()->setSize(p->getNext()->getSize()+1);
                            p->getPrev()->setNext(p->getNext());
                            p->getNext()->setPrev(p->getPrev());
                            delete p;
                        }
                        else if (p->getPrev()->getCellContents()==Ocean::FISH)
                        {
                            p->getPrev()->setSize(p->getPrev()->getSize()+1);
                            p->getPrev()->setNext(p->getNext());
                            p->getNext()->setPrev(p->getPrev());
                            delete p;
                        }
                        else
                        {
                            p->setCellContents(Ocean::FISH);
                        }

                    }
                    else
                    {
                        if(indexOfNode==postion-p->getSize()+1)
                        {




                            if(p->getPrev()->getCellContents()==Ocean::FISH)
                            {
                                p->getPrev()->setSize(p->getPrev()->getSize()+1);
                                p->setSize(p->getSize()-1);


                            }
                            else
                            {

                                LinkedListNode* newnode = new LinkedListNode(Ocean::FISH,-1,1,p,p->getPrev());
                                p->setPrev(newnode);
                                p->setSize(p->getSize()-1);
                                newnode->getPrev()->setNext(newnode);



                            }

                        }
                        else if(indexOfNode==postion)
                        {
                            if(p->getNext()->getCellContents()==Ocean::FISH)
                            {
                                p->getNext()->setSize(p->getNext()->getSize()+1);
                                p->setSize(p->getSize()-1);



                            }
                            else
                            {

                                LinkedListNode* newnode = new LinkedListNode(Ocean::FISH,-1,1,p->getNext(),p);
                                p->setNext(newnode);
                                p->setSize(p->getSize()-1);
                                newnode->getNext()->setPrev(newnode);



                            }

                        }
                        else
                        {
                            LinkedListNode*temp=p->getNext();
                            int S1,S2;
                            S1=indexOfNode-(postion-p->getSize())-1;
                            S2=postion-indexOfNode;
                            p->setSize(S1);

                            LinkedListNode* node1 = new LinkedListNode(Ocean::FISH,-1,1,0,p);
                            p->setNext(node1);

                            LinkedListNode* node2 = new LinkedListNode(Ocean::EMPTY,-1,S2,temp,node1);
                            node1->setNext(node2);
                            if(temp!=NULL)
                            {
                                temp->setPrev(node2);
                            }
                            else
                            {
                                list.setTail(node2);
                            }


                        }

                    }
                    i=-1;




                }
                else
                {
                    i=-1;
                }



            }
            else
            {
                p=p->getNext();
            }








        }






    }


    // Your solution here, but you should probably leave the following line
    //   at the end.
    pointerToRun=list.getHead();
    check();
}

/*
 *  addShark() (with two parameters) places a newborn shark in cell (x, y) if
 *  the cell is empty.  A "newborn" shark is equivalent to a shark that has
 *  just eaten.  If the cell is already occupied, leave the cell as it is.
 *  The final run-length encoding should be compressed as much as possible;
 *  there should not be two consecutive runs of sharks with the same degree
 *  of hunger.
 *  @param x is the x-coordinate of the cell to place a shark in.
 *  @param y is the y-coordinate of the cell to place a shark in.
 */

void RunLengthEncoding::addShark(int x, int y)
{

    int indexOfNode=(width*doWarpping(y,height))+doWarpping(x,width)+1;
    LinkedListNode * p=list.getHead();
    if(indexOfNode==1)
    {
        if(p->getCellContents()==Ocean::EMPTY)
        {
            if(p->getSize()==1)
            {
                if(p->getNext()->getCellContents()==Ocean::SHARK&&p->getNext()->getElapsedTime()==0)
                {
                    p->getNext()->setSize(p->getNext()->getSize()+1);
                    list.setHead(p->getNext());
                    list.getHead()->setPrev(0);
                    delete  p;
                }
                else
                {
                    p->setCellContents(Ocean::SHARK);
                    p->setElapsedTime(0);
                }

            }
            else
            {
                LinkedListNode* newnode = new LinkedListNode(Ocean::SHARK,0,1,p,0);
                p->setPrev(newnode);
                p->setSize( p->getSize()-1);
                list.setHead(newnode);

            }


        }
    }
    else if(indexOfNode==width*height)
    {
        if(list.getTail()->getCellContents()==Ocean::EMPTY)
        {
            if(list.getTail()->getSize()==1)
            {

                if(list.getTail()->getPrev()->getCellContents()==Ocean::SHARK&&list.getTail()->getPrev()->getElapsedTime()==0)
                {
                    LinkedListNode*q= list.getTail();
                    list.getTail()->getPrev()->setSize(list.getTail()->getPrev()->getSize()+1);
                    list.setTail(list.getTail()->getPrev());
                    list.getTail()->setNext(0);
                    delete  q;
                }
                else
                {
                    list.getTail()->setCellContents(Ocean::SHARK);
                }
            }
            else
            {
                LinkedListNode* newnode = new LinkedListNode(Ocean::SHARK,0,1,0,list.getTail());
                list.getTail()->setNext(newnode);
                list.getTail()->setSize(list.getTail()->getSize()-1);
                list.setTail(newnode);


            }


        }
    }
    else
    {

        int postion=0;
        LinkedListNode * p=list.getHead();
        int i=1;
        while(p!=NULL&&i>0)
        {
            postion+=p->getSize();

            if(indexOfNode<=postion)
            {
                if(p->getCellContents()==Ocean::EMPTY)
                {
                    if(p->getSize()==1)
                    {
                        if(p->getNext()->getCellContents()==Ocean::SHARK&&p->getNext()->getElapsedTime()==0&&p->getPrev()->getElapsedTime()==0&&p->getPrev()->getCellContents()==Ocean::FISH)
                        {

                            p->getPrev()->setSize(p->getPrev()->getSize()+1+p->getNext()->getSize());
                            p->getPrev()->setNext(p->getNext()->getNext());
                            p->getNext()->getNext()->setPrev(p->getPrev());
                            delete p->getNext();
                            delete p;


                        }
                        else if (p->getNext()->getCellContents()==Ocean::FISH&&p->getNext()->getElapsedTime()==0)
                        {
                            p->getNext()->setSize(p->getNext()->getSize()+1);
                            p->getPrev()->setNext(p->getNext());
                            p->getNext()->setPrev(p->getPrev());
                            delete p;
                        }
                        else if (p->getPrev()->getCellContents()==Ocean::SHARK&&p->getPrev()->getElapsedTime()==0)
                        {
                            p->getPrev()->setSize(p->getPrev()->getSize()+1);
                            p->getPrev()->setNext(p->getNext());
                            p->getNext()->setPrev(p->getPrev());
                            delete p;
                        }
                        else
                        {
                            p->setCellContents(Ocean::SHARK);
                        }

                    }
                    else
                    {
                        if(indexOfNode==postion-p->getSize()+1)
                        {




                            if(p->getPrev()->getCellContents()==Ocean::SHARK&&p->getPrev()->getElapsedTime()==0)
                            {
                                p->getPrev()->setSize(p->getPrev()->getSize()+1);
                                p->setSize(p->getSize()-1);


                            }
                            else
                            {

                                LinkedListNode* newnode = new LinkedListNode(Ocean::SHARK,0,1,p,p->getPrev());
                                p->setPrev(newnode);
                                p->setSize(p->getSize()-1);
                                newnode->getPrev()->setNext(newnode);



                            }

                        }
                        else if(indexOfNode==postion)
                        {
                            if(p->getNext()->getCellContents()==Ocean::SHARK&&p->getNext()->getElapsedTime()==0)
                            {
                                p->getNext()->setSize(p->getNext()->getSize()+1);
                                p->setSize(p->getSize()-1);



                            }
                            else
                            {

                                LinkedListNode* newnode = new LinkedListNode(Ocean::SHARK,0,1,p->getNext(),p);
                                p->setNext(newnode);
                                p->setSize(p->getSize()-1);
                                newnode->getNext()->setPrev(newnode);



                            }

                        }
                        else
                        {

                            LinkedListNode*temp=p->getNext();
                            int S1,S2;
                            S1=indexOfNode-(postion-p->getSize())-1;
                            S2=postion-indexOfNode;
                            p->setSize(S1);

                            LinkedListNode* node1 = new LinkedListNode(Ocean::SHARK,0,1,0,p);
                            p->setNext(node1);

                            LinkedListNode* node2 = new LinkedListNode(Ocean::EMPTY,-1,S2,temp,node1);
                            node1->setNext(node2);
                            if(temp!=NULL)
                            {
                                temp->setPrev(node2);
                            }
                            else
                            {
                                list.setTail(node2);
                            }



                        }
                    }
                    i=-1;




                }
                else
                {
                    i=-1;
                }



            }
            else
            {
                p=p->getNext();
            }








        }






    }
    pointerToRun=list.getHead();

    // Your solution here, but you should probably leave the following line
    //   at the end.
    check();
}

/*
 *  check() walks through the run-length encoding and prints an error message
 *  if two consecutive runs have the same contents, or if the sum of all run
 *  lengths does not equal the number of cells in the ocean.
 */

void RunLengthEncoding::check()
{
    int type1,type2,elapsedtime1,elapsedtime2;
    int size=0;
    LinkedListNode *p=list.getHead();
    while(p->getNext()!=NULL)
    {
        type1=p->getCellContents();
        type2=p->getNext()->getCellContents();
        elapsedtime1=p->getElapsedTime();
        elapsedtime2=p->getNext()->getElapsedTime();

        if((type1==type2)&&(elapsedtime1==elapsedtime2))
        {

            cout<<"Sorry two runs have exactly the same type of contents !!\n";
            break;
        }
        if(p->getSize()<1)
        {
            cout<<"Sorry there is an error1 !!\n";
        }
        size+=p->getSize();
        p=p->getNext();


    }
    if(p->getSize()<1)
    {
        cout<<"Sorry there is an error2 !!\n";
    }

    size+=p->getSize();

    if(size!=height*width)
    {

        cout<<"Sorry there is an error 3!!\n";

    }


}
