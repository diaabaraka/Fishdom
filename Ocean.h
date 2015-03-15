
#ifndef OCEAN_H
#define OCEAN_H
#include "Cell.h"

/*
 *  The Ocean class defines an object that models an ocean full of sharks and
 *  fish.  Descriptions of the methods you must implement appear below.  They
 *  include a constructor of the form
 *
 *      public Ocean(int i, int j, int starveTime);
 *
 *  that creates an empty ocean having width i and height j, in which sharks
 *  starve after starveTime timesteps.
 *
 *  See the README file accompanying this project for additional details.
 */

class Ocean
{
public:
    Ocean();
    Ocean(int i, int j, int starveTime);
    ~Ocean();
    int width();
    int height();
    int starveTime();
    int doWarpping(int coordinate,int maxCoordinate);
    int getNeighbours(int x,int y,int cellContents);
    void addFish(int x, int y);
    void addShark(int x, int y);
    int cellContents(int x, int y);
   Ocean* miniMax();
    Ocean *timeStep();
    void addShark(int x, int y, int feeding);
    int sharkFeeding(int x, int y);
    /*
    *  Do not rename these constants or change their values
    */
    static const int EMPTY = 0;
    static const int SHARK = 1;
    static const int FISH = 2;
private:
    /*
       *  Define any variables associated with an Ocean object here.  These
       *  variables MUST be private.
       */
    int width1;
    int height1;
    int starveTime1;
    Cell **arr;



};

#endif // OCEAN_H
