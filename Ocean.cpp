#include "Ocean.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
//Empty Constructor
Ocean::Ocean()
{
    starveTime1=100;
    height1=50;
    width1=25;
    arr=new Cell*[height1];
    for (int k=0; k<height1 ; k++ )
    {
        arr[k]=new Cell[width1];
    }
}


/*
   *  Ocean() is a constructor that creates an empty ocean having width i and
   *  height j, in which sharks starve after starveTime timesteps.
   *  @param i is the width of the ocean.
   *  @param j is the height of the ocean.
   *  @param starveTime is the number of timesteps sharks survive without food.
   */
Ocean::Ocean(int i, int j, int starveTime)
{
    starveTime1=starveTime;
    height1=j;
    width1=i;
    arr=new Cell*[height1];
    for (int k=0; k<height1 ; k++ )
    {
        arr[k]=new Cell[width1];
    }




}

//Destructor
Ocean::~Ocean()
{

    for (int k=0; k<height1 ; k++ )
    {
        delete(arr[k]);
    }
    delete(arr);

    // Your solution here.
}
/**
 *  doWarpping() returns the correct coordinate after warpping.
 *  @return the correct coordinate after warpping.
 */
int Ocean::doWarpping(int coordinate,int maxCoordinate)
{

    int x=coordinate%maxCoordinate;
    if(x>=0)
    {
        return x;
    }
    return (x+maxCoordinate);

}
int Ocean ::getNeighbours(int x,int y,int requiredContents)
{
    int count=0;
    bool checkVisit[height1][width1];
    for(int i=0; i<height1; i++)
    {

        for(int j=0; j<width1; j++)
        {

            checkVisit[i][j]=true;
        }
    }
    for(int j=y-1; j<=y+1; j++)
    {

        for(int i=x-1; i<=x+1; i++)
        {

            if(!(i==x&&j==y)&&checkVisit[doWarpping(j,height1)][doWarpping(i,width1)])
            {

                if(arr[doWarpping(j,height1)][doWarpping(i,width1)].getCellContents()==requiredContents)
                {
                    count++;
                    checkVisit[doWarpping(j,height1)][doWarpping(i,width1)]=false;


                }





            }


        }



    }
    return count;
}
/**
 *  width() returns the width of an Ocean object.
 *  @return the width of the ocean.
 */
int Ocean::width()
{

    return width1;
}

/**
 *  height() returns the width of an Ocean object.
 *  @return the height of the ocean.
 */
int Ocean::height()
{
    // Replace the following line with your solution.
    return height1;
}

/*
 *  starveTime() returns the number of timesteps sharks survive without food.
 *  @return the number of timesteps sharks survive without food.
 */

int Ocean::starveTime()
{
    // Replace the following line with your solution.
    return starveTime1;
}


/*
 *  addFish() places a fish in cell (x, y) if the cell is empty.  If the
 *  cell is already occupied, leave the cell as it is.
 *  @param x is the x-coordinate of the cell to place a fish in.
 *  @param y is the y-coordinate of the cell to place a fish in.
 */

void Ocean::addFish(int x, int y)
{
    x=doWarpping(x,width1);
    y=doWarpping(y,height1);
    if(arr[y][x].getCellContents()==EMPTY)
    {
        arr[y][x].setCellContents(FISH);
    }

}

/*
 *  addShark() (with two parameters) places a newborn shark in cell (x, y) if
 *  the cell is empty.  A "newborn" shark is equivalent to a shark that has
 *  just eaten.  If the cell is already occupied, leave the cell as it is.
 *  @param x is the x-coordinate of the cell to place a shark in.
 *  @param y is the y-coordinate of the cell to place a shark in.
 */

void Ocean::addShark(int x, int y)
{
    x=doWarpping(x,width1);
    y=doWarpping(y,height1);

    if(arr[y][x].getCellContents()==EMPTY)
    {
        arr[y][x].setCellContents(SHARK);
        arr[y][x].setElapsedTime(0);
    }
}

/*
 *  cellContents() returns EMPTY if cell (x, y) is empty, FISH if it contains
 *  a fish, and SHARK if it contains a shark.
 *  @param x is the x-coordinate of the cell whose contents are queried.
 *  @param y is the y-coordinate of the cell whose contents are queried.
 */

int Ocean::cellContents(int x, int y)
{

    return arr[y][x].getCellContents();
}

Ocean* Ocean:: miniMax()
{


    Ocean*sea2=new Ocean(width1, height1, starveTime1);
    int min=8;
    int xmin;
    int ymin;
    bool bn=false;
    for(int i=0; i<height1; i++)
    {
        for(int j=0; j<width1; j++)
        {
            if(arr[i][j].getCellContents()==FISH)
            {
                bn=false;
                if(getNeighbours(j,i,SHARK)==0)
                {
                    sea2->addFish(j,i);



                }
                else
                {
                    min=8;
                    for(int x=i-1; x<=i+1; x++)
                    {

                        for(int y=j-1; y<=j+1; y++)
                        {
                            int x1=doWarpping(x,height1);
                            int y1=doWarpping(y,width1);

                            if(arr[x1][y1].getCellContents()==EMPTY&&getNeighbours(y1,x1,SHARK)==0)
                            {
                                bn=true;
                                if(getNeighbours(y1,x1,FISH)-1<=min&&sea2->arr[x1][y1].getCellContents()==EMPTY)
                                {
                                    min=getNeighbours(y1,x1,FISH)-1;
                                    xmin=x1;
                                   ymin=y1;

                                }

                            }
                        }
                    }
                    if(bn==true){
                        sea2->addFish(ymin,xmin);
                    }
                    else{
                        sea2->addFish(j,i);
                    }



                }

            }   else if(arr[i][j].getCellContents()==SHARK)
            {





                sea2->addShark(j,i);
                sea2->arr[i][j].setElapsedTime(arr[i][j].getElapsedTime());


            }





        }
    }
  return sea2;

}

/*
 *  timeStep() performs a simulation timestep as described in README.
 *  @return an ocean representing the elapse of one timestep.
 */

Ocean* Ocean::timeStep()
{
Ocean*sea2=new Ocean(width1, height1, starveTime1);
    for(int i=0; i<height1; i++)
    {
        for(int j=0; j<width1; j++)
        {
            if(arr[i][j].getCellContents()==SHARK)
            {


                if(getNeighbours(j,i,FISH)>0)
                {


                    sea2->addShark(j,i);


                }
                else
                {

                    if(arr[i][j].getElapsedTime()+1<starveTime1)
                    {
                        sea2->addShark(j,i);
                        sea2->arr[i][j].setElapsedTime(arr[i][j].getElapsedTime()+1);


                    }
                }
            }
            else if(arr[i][j].getCellContents()==FISH)
            {
                if(getNeighbours(j,i,SHARK)==0)
                {
                    sea2->addFish(j,i);



                }
                else if(getNeighbours(j,i,SHARK)>=2)
                {
                    sea2->addShark(j,i);
                }

            }
            else
            {
                if(getNeighbours(j,i,FISH)>=2&&getNeighbours(j,i,SHARK)<=1)
                {
                    sea2->addFish(j,i);



                }
                else if(getNeighbours(j,i,FISH)>=2&&getNeighbours(j,i,SHARK)>=2)
                {
                    sea2->addShark(j,i);
                }





            }









        }



    }


    return sea2;

}

/*
 *  The following method is required for Part II.
 */

/*
 *  addShark() (with three parameters) places a shark in cell (x, y) if the
 *  cell is empty.  The shark's hunger is represented by the third parameter.
 *  If the cell is already occupied, leave the cell as it is.  You will need
 *  this method to help convert run-length encodings to Oceans.
 *  @param x is the x-coordinate of the cell to place a shark in.
 *  @param y is the y-coordinate of the cell to place a shark in.
 *  @param feeding is an integer that indicates the shark's hunger.  You may
 *         encode it any way you want; for instance, "feeding" may be the
 *         last timestep the shark was fed, or the amount of time that has
 *         passed since the shark was last fed, or the amount of time left
 *         before the shark will starve.  It's up to you, but be consistent.
 */

void Ocean::addShark(int x, int y, int feeding)
{
    if(arr[y][x].getCellContents()==EMPTY)
    {
        arr[y][x].setCellContents(SHARK);
        arr[y][x].setElapsedTime(feeding);
    }
}

/*
 *  The following method is required for Part III.
 */

/*
 *  sharkFeeding() returns an integer that indicates the hunger of the shark
 *  in cell (x, y), using the same "feeding" representation as the parameter
 *  to addShark() described above.  If cell (x, y) does not contain a shark,
 *  then its return value is undefined--that is, anything you want.
 *  Normally, this method should not be called if cell (x, y) does not
 *  contain a shark.  You will need this method to help convert Oceans to
 *  run-length encodings.
 *  @param x is the x-coordinate of the cell whose contents are queried.
 *  @param y is the y-coordinate of the cell whose contents are queried.
 */

int Ocean::sharkFeeding(int x, int y)
{
    return arr[y][x].getElapsedTime();
}



