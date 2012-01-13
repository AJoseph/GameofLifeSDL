#include "grid.h"

/*
Constructor
The constructor initializes all cells in the (viewable) grid to be DEAD
*/

Grid::Grid()
{
    for (int row = 1; row <= MAXROW; row++)
        for (int col = 1; col <= MAXCOL; col++)
        {
            grid[row][col] = DEAD;
            generation[row][col] = 0;
        }
}

/*
The printgrid() function prints out the viewable grid.
It prints out the essential grid only.
The extra spaces are added in the function to allow easier viewing.
*/

void Grid::printgrid()
{
    for (int i = 0; i <= MAXROW+1; i++)
    {
        for (int j = 0; j <= MAXCOL+1; j++)
        {
            if (i==0)
            {
                if (j==0)
                    std::cout << "   ";
                else
                    if (j<=MAXCOL)
                    {
                        if (j < 10)
                            std::cout << " ";
                        std::cout << " " << j;
                    }
            }
            else
                if (i<=MAXROW)
                {
                    if (j==0)
                    {
                        std::cout << " " << i;
                        if (i < 10)
                            std::cout << " ";
                    }
                    else
                        if (j<=MAXCOL)
                        {
                            std::cout << "  ";
                            if (grid[i][j] == ALIVE)
                                std::cout << '*';
                            else
                                std::cout << grid[i][j];
                        }
                }
        }
        std::cout << std::endl;
    }
}

/*
The initialize() function gets the user input and sets the first pattern.
The user gets to enter a series of co-ordinates and there is check for boundary.
Termination condition is -1 -1 as input.
*/

void Grid::initialize()
{
    int row, col;

    std::cout << " Enter positions on Grid as \"row col\" terminating them with -1 -1 to terminate input " << std::endl;

    std::cin >> row >> col;

    while ((row != -1) || (col != -1))
    {
        if ((row >= 1) && (row <= MAXROW))
        {
            if ((col >= 1) && (col <= MAXCOL))
            {
                grid[row][col] = ALIVE;
                generation[row][col] = 1;
            }
            else
                std::cout << "Column "<< col << " - out of range."<< std::endl;
        }
        else
            std::cout << "Row "<< row << " - out of range."<< std::endl;
        std::cin >> row >> col;
    }

}


/*
The updategrid() function is the one that updates the grid for the next generation.
The function basically calls the surroundingcells() function to find the living cells around a particular cell and then decides
whether it lives or dies in the next generation.
After it updates the nextgen it compares with the current gen and returns a boolean to state if the game is over or not.
*/
bool Grid::updategrid()
{
    Grid* nextgen = new Grid;

    for (int i = 1; i <= MAXROW; i++)
        for (int j = 1; j <= MAXCOL; j++)
        {
            nextgen->generation[i][j] = this->generation[i][j];
            switch (surroundingcells(i,j))
            {
                case 2:
                    nextgen->grid[i][j] = this->grid[i][j];
                    if(nextgen->grid[i][j] == ALIVE)
                        nextgen->generation[i][j]++;
                    break;
                case 3:
                    if (this->grid[i][j] == ALIVE)
                        nextgen->generation[i][j]++;
                    else
                        nextgen->generation[i][j] = 1;
                    nextgen->grid[i][j] = ALIVE;
                    break;
                default:
                    nextgen->grid[i][j] = DEAD;
                    nextgen->generation[i][j] = 0;
            }
        }

    if (*this == *nextgen)
    {
        delete nextgen;
        return true;
    }
    else
    {
        *this = *nextgen;
        delete nextgen;
        return false;
    }
}

/*
The surroundingcells() function finds the number of living cells around a particular cell.
*/

int Grid::surroundingcells(int row, int col)
{
    int sum = 0;

    /*
    The below loop calculates the number of cells in a 3x3 square grid.
    The central cell is the one whose count of neigbours is needed. Hence we subtract that
    particular cell's value from the total sum value.
    */
    for (int i = row-1; i <= row + 1; i++)
        for (int j = col-1; j <= col+1; j++)
            sum+= grid[i][j];

    sum-= grid[row][col];

    return sum;
}


/*
The operator (==) overloaded function checks to see if the two compared grids are same.
If any cell in both grids are not same, it returns false else true.
*/
bool Grid::operator ==(const Grid& next)
{
    for (int row = 1; row <= MAXROW; row++)
    {
        for (int col = 1; col <= MAXCOL; col++)
        {
            if (grid[row][col] != next.grid[row][col])
                return false;
        }
    }
    return true;
}

