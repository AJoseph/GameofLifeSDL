#include "grid.h"
#include "SDL.h"

SDL_Surface* screen, *grid, *genimage; //create surface for screen, grid and image for generations - declared global to use in functions

SDL_Rect genrect[11]; //having one more so that we can reference easily from 1 to 10

/*
The getuserchoice() function finds out from the user if he wants to continue with the update on grid or not.
*/
bool getuserchoice()
{
    int ch;

    bool loop = true;

    while (loop)
    {
        std::cout << "Do you want to update the board.? Pls specify only y/n." << std::endl;

        do
        {
            ch = std::cin.get();
        } while (ch == '\n' || ch == ' ' || ch== '\t');

        if (ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n')
            loop = false;
    }

    return (ch== 'Y' || ch=='y');
}

/*
The setgenrect function assigns the x & y co-ordinates for each of the images in the generation image.
The w and h of the rectangle are however set at 20 each.
*/
void setgenrect(SDL_Rect* genrect)
{
    for (int i = 1; i < 11; i++)
    {
        genrect[i].y = 1;
        genrect[i].x = (i - 1) * 21 + 1;
        genrect[i].w = 20;
        genrect[i].h = 20;
    }
}

void displaySDLgrid(Grid* newboard)
{
    SDL_BlitSurface(grid,NULL,screen,NULL);

    SDL_Rect scrrect;

    for (int row = 1; row <= MAXROW; row++)
        for (int col = 1; col <= MAXCOL; col++)
        {
            if (newboard->getstate(row,col)==ALIVE)
            {
                scrrect.w = 20;
                scrrect.h = 20;
                scrrect.x = (col-1) * 25 + 6;
                scrrect.y = (row-1) * 25 + 6;
                int gen = newboard->getgen(row,col);
                if (gen > 10)
                    gen = 10;
                std::cout << "Row " << row << " Col " << col << " Gen " << gen << std::endl;
                SDL_BlitSurface(genimage,&genrect[gen],screen,&scrrect);
            }
        }
    SDL_Flip(screen);

}

int main(int argc, char * argsv[])
{
    Grid newboard;

    SDL_Init(SDL_INIT_EVERYTHING); //init SDL

	screen = SDL_SetVideoMode(460,410,32,SDL_SWSURFACE); //create a 460 by 410 window

    bool gameover = false;

    Uint32 bgcolor = SDL_MapRGB(screen->format,0x00,0x00,0x00); // set a background color to black

	SDL_FillRect(screen,&screen->clip_rect,bgcolor); //apply the background color to the entire screen area

    std::cout << "Game of Life" << std::endl;

    grid = SDL_DisplayFormat(SDL_LoadBMP("grid.bmp")); //load the grid image

    SDL_BlitSurface(grid,NULL,screen,NULL); //apply the grid image to the screen

    newboard.printgrid();

    SDL_Flip(screen); //show the grid on the screen

    genimage = SDL_DisplayFormat(SDL_LoadBMP("generation.bmp")); //load the generation image

    setgenrect(genrect); //assign rectangle co-ordinates as per the generation image

    newboard.initialize();

    std::cout << "After plotting initial positions..." << std::endl;

    newboard.printgrid();

    displaySDLgrid(&newboard);

    while (!gameover)
    {
        if (getuserchoice())

        {
            gameover = newboard.updategrid();

            newboard.printgrid();

            displaySDLgrid(&newboard);

            if (gameover)
                std::cout << "The next gen is the same as the current generation. No more generations possible." << std::endl;
        }

        else
            gameover = true;
    }


    SDL_FreeSurface(genimage);
    SDL_FreeSurface(grid);

    SDL_Quit();

    std::cout << "Thanks for trying out the Game of Life" << std::endl;

}


