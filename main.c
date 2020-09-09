#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "grid.h"
#include "utils.h"


// TODO Clean this, separate files

// ANCHOR There is the quit func
void stop_it(SDL_Window *w, SDL_Renderer *r)
{
    if (r != NULL)
    {
        SDL_DestroyRenderer(r);
    }
    if (w != NULL)
    {
        SDL_DestroyWindow(w);
    }
    SDL_Quit();

    exit(EXIT_FAILURE);
}

int main(void)
{
    srand(time(NULL));

    SDL_Window *w = NULL;
    SDL_Event event;
    SDL_Renderer *renderer = NULL;
    SDL_Color blue = {0, 0, 255, 255};

    // main loop quit flag
    bool terminate = false;
    // spacebar stops the games
    bool stop = true;

    //  Initlialize SDL_Video
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_ERROR);
    }

    //  Creates the window and shows it
    w = SDL_CreateWindow("Another Game of Life",
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         W_WIDTH,
                         W_HEIGTH,
                         SDL_WINDOW_SHOWN |
                             SDL_WINDOW_RESIZABLE);
    //  Test if W succesfully created
    if (w == NULL)
    {
        fprintf(stderr, "Erreur ouverture fenetre %s\n", SDL_GetError());
        stop_it(w, renderer);
    }

    //  Create the renderer
    renderer = SDL_CreateRenderer(w, -1, SDL_RENDERER_SOFTWARE);
    //  Error test
    if (renderer == NULL)
    {
        fprintf(stderr, "Erreur renderer: %s\n", SDL_GetError());
        stop_it(w, renderer);
    }

    //  Set size of renderer
    if (SDL_RenderSetLogicalSize(renderer, W_WIDTH, W_HEIGTH) != 0)
    {
        fprintf(stderr, "Erreur Set renderer Logical size: %s\n", SDL_GetError());
        stop_it(w, renderer);
    }

    //MAIN INIT PHASE

    int **cells;
    int **next_cells;
    cells = init_grid_rand(SIZE_CELL);
    next_cells = create_mat_int(SIZE_CELL);

    render_cell_grid(w, renderer, SIZE_CELL, cells);


    while (!terminate)
    {
        // while there are events ...
        // handle them, in this case only execute the quit ones
        while (SDL_PollEvent(&event) != 0)
        {
            // User wants to quit
            if ( event.type == SDL_QUIT )
            {
                db("Received an SDL_QUIT event");
                db("Quiting main loop");
                terminate = true;
            }
            else if ( event.type == SDL_KEYDOWN)
            {
                //select action based on keypress
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    db("SPACE pressed ...");
                    stop = stop ? false : true;
                    break;
                
                default:
                    break;
                }
            }
            
        }


        if (!stop)
        {
            SDL_Delay(100);

            set_next_grid(cells, next_cells, renderer);
            render_cell_grid(w, renderer, SIZE_CELL, next_cells);
            copy_mat(next_cells, cells);
        }
    }

    SDL_DestroyRenderer(renderer);
    //  Destroys window
    SDL_DestroyWindow(w);
    //  Stops SDL_process
    SDL_Quit();

    free_grid(cells, SIZE_CELL);
    free_grid(next_cells, SIZE_CELL);
    return 0;
}
