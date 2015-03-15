#include "Cell.h"
Cell::Cell()
{
    cellContents=0;
    elapsedTime=-1;
}
Cell::Cell(int cellContents1,int elapsedTime1)
{
    cellContents=cellContents1;
    elapsedTime=elapsedTime1;
}

void Cell::setCellContents(int cellContents1)
{
    cellContents=cellContents1;


}
void Cell::setElapsedTime(int elapsedTime1)
{

    elapsedTime=elapsedTime1;
}
int Cell::getCellContents()
{

    return cellContents;
}
int Cell::getElapsedTime()
{
    return elapsedTime;
}
