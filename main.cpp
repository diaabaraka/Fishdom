/* DO NOT CHANGE THIS FILE (except as noted). */
/* YOUR SUBMISSION MUST WORK CORRECTLY WITH _OUR_ COPY OF THIS FILE. */

/* (You may wish to make temporary changes or insert cout statements    */
/* while testing your code.  When you're finished testing and debugging,     */
/* though, make sure your code works with the original version of this file. */

/*
 *  This file is a program that runs and animates a simulation of
 *  Sharks and Fish.
 *
 *  It takes up to four parameters.  The first two specify
 *  the width and height of the ocean.  The third parameter specifies the value
 *  of starveTime.  For example, if you run with the following parameters
 *
 *         25 25 1
 *
 *  then it will animate a 25x25 ocean with a starveTime of 1.  If you run
 *  the file with no parameters, by default it will animate a 50x25
 *  ocean with a starveTime of 3.  With some choices of parameters, the ocean
 *  quickly dies out; with others, it teems forever.
 *
 *  @author Jonathan Shewchuk with some editing by Mahmoud Fouad
 */

#include <iostream>
#include "Ocean.h"
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include"RunLengthEncoding.h"
using namespace std;

/*
 *  Default parameters.  (You may change these if you wish.)
 */

int i = 5;                             // Default ocean width
int j = 5;                            // Default ocean height
int starveTime = 2;           // Default shark starvation time

/*
 *  paint() prints an Ocean.
 */

void paint(Ocean* sea)
{
    int width = sea->width();
    int height = sea->height();

    /* Draw the ocean. */
    for (int x = 0; x < width + 2; x++)
    {
        cout << "-";
    }
    cout << endl;
    for (int y = 0; y < height; y++)
    {
        cout << "|";
        for (int x = 0; x < width; x++)
        {
            int contents = sea->cellContents(x, y);
            if (contents == Ocean::SHARK)
            {
                cout << 'S';
            }
            else if (contents == Ocean::FISH)
            {
                cout << '~';
            }
            else
            {
                cout << ' ';
            }
        }
        cout << "|\n";
    }
    for (int x = 0; x < width + 2; x++)
    {
        cout << "-";
    }
    cout << endl;
}

/*
 *  main() reads the parameters and performs the simulation and animation.
 */

int main(int argc, char **argv)
{

    /*
     *  Read the input parameters.
     */

    if (argc > 1)
    {
        i = atoi(argv[1]);
    }

    if (argc > 2)
    {
        j = atoi(argv[2]);
    }

    if (argc > 3)
    {
        starveTime = atoi(argv[3]);
    }

    /*
     *  Create the initial ocean.
    //     */
//
//    Ocean sea(4, 4,5);
//    sea.addShark(2,1);
//    sea.addFish(1,0);
////    sea.addFish(0,3);
////    sea.addShark(2,1);
//    sea=*sea.miniMax();
//





//
//int type[]={0};
//int length[]={9};
//RunLengthEncoding* sea2=new RunLengthEncoding (3,3,5,type,1,length,1);
//sea2->addFish(0,0);
//
//sea2->addFish(0,1);
//
//int resullt,sizer;
//sea2->nextRun(&resullt,&sizer);
//cout<<resullt<<"\n"<<sizer<<"\n";
//sea2->nextRun(&resullt,&sizer);
//cout<<resullt<<"\n"<<sizer<<"\n";
////
////
////
//    Ocean *sea=(sea2->toOcean());
Ocean *sea=new Ocean(4,4,1);
sea->addFish(3,0);
sea->addFish(1,1);
sea->addFish(3,3);
sea->addShark(0,1);
sea->addShark(2,1);
//sea->addShark(4,2);
        sea=sea->miniMax();


    /*
     *  Generate the map and add sharks and fish to it
     *  Visit each cell (in a roundabout order); RANDOMLY (with a specific seed) place a fish, shark,
     *  or nothing in each.
     *  Briefly, put your seed as a constant integer (say 0) to create the same map in each run
     *  If you change the seed, the generated map will differ.
     */

    // You generation goes here

    /*
     *  Perform timesteps forever.
     */
//
    while (true)                                                // Loop forever
    {
        system("cls");
        paint(sea);
//          For fun, you might wish to change the delay in the next line.
        Sleep(10000);                    // Wait one second
        sea = (sea->timeStep());           // Simulate a timestep
    }
    return 0;
}
