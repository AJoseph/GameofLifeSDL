#ifndef GRID_H
#define GRID_H

#include <iostream>

#define MAXROW 16
#define MAXCOL 18

enum state {DEAD, ALIVE};

class Grid
{
    private:

        state grid[MAXROW + 2][MAXCOL + 2];
        int generation[MAXROW + 2][MAXCOL + 2];

    public:

        Grid(); //constructor

        void initialize(void);

        bool updategrid();

        void printgrid(void);

        int surroundingcells(int row, int col);

        bool operator ==(const Grid& next);

        state getstate(int row, int col)
        {
            return grid[row][col];
        }

        int getgen(int row, int col)
        {
            return generation[row][col];
        }

};


#endif // GRID_H
