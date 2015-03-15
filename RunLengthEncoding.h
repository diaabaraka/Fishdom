#ifndef RUNLENGTHENCODING_H
#define RUNLENGTHENCODING_H
#include "MyLinkedList.h"

#include "Ocean.h"


/*
 *  The RunLengthEncoding class defines an object that run-length encodes an
 *  Ocean object.  Descriptions of the methods you must implement appear below.
 *  They include constructors of the form
 *
 *      public RunLengthEncoding(int i, int j, int starveTime);
 *      public RunLengthEncoding(int i, int j, int starveTime,
 *                               int[] runTypes, int runTypesSize, int[] runLengths, int runLengthsSize) {
 *      public RunLengthEncoding(Ocean ocean) {
 *
 *  that create a run-length encoding of an Ocean having width i and height j,
 *  in which sharks starve after starveTime timesteps.
 *
 *  The first constructor creates a run-length encoding of an Ocean in which
 *  every cell is empty.  The second constructor creates a run-length encoding
 *  for which the runs are provided as parameters.  The third constructor
 *  converts an Ocean object into a run-length encoding of that object.
 *
 *  See the README file accompanying this project for additional details.
 */



class RunLengthEncoding
{
public:
    RunLengthEncoding(int i, int j, int starveTime);
    RunLengthEncoding(int i, int j, int starveTime, int* runTypes, int runTypesSize, int* runLengths, int runLengthsSize);
    RunLengthEncoding(Ocean sea);
    ~RunLengthEncoding();
    int doWarpping(int coordinate,int maxCoordinate);
    void restartRuns();
    void nextRun(int* result, int *size);
    Ocean* toOcean();
    void addFish(int x, int y);
    void addShark(int x, int y);
protected:
private:
    void check();
    int height;
    int width;
    int starveTime;
    MyLinkedList list;
    LinkedListNode* pointerToRun;
    /*
     *  Define any variables associated with a RunLengthEncoding object here.
     *  These variables MUST be private.
     */

};

#endif // RUNLENGTHENCODING_H

