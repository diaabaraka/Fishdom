#ifndef CELL_H
#define CELL_H


class Cell
{
public:
    Cell();
    Cell(int cellContents1,int elapsedTime1);

    void setCellContents(int cellContents1);
    void setElapsedTime(int elapsedTime1);
    int getCellContents();
    int getElapsedTime();

private:
    int cellContents;
    int elapsedTime;
};

#endif // CELL_H
