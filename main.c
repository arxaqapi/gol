#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"
#include <time.h>

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

    bool terminate = false;

    //  Initlialize SDL_Video
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_ERROR);
    }

    //  Creates the window and shows it
    w = SDL_CreateWindow("Test",
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
    draw_grid(w, renderer, SIZE_CELL);

    for (int i = 0; i < 100; i++)
    {
        //it
        SDL_Delay(200);

        set_next_grid(cells, next_cells, renderer);
        render_cell_grid(w, renderer, SIZE_CELL, next_cells);
        draw_grid(w, renderer, SIZE_CELL);

        cp_mat(next_cells, cells);
    }

    while (!terminate)
    {
        SDL_WaitEvent(&event);
        if (event.window.event == SDL_KEYDOWN)
        {
            terminate = true;
        }
    }

    SDL_DestroyRenderer(renderer);
    //  Destroys window
    SDL_DestroyWindow(w);
    //  Stops SDL_process
    SDL_Quit();
    return 0;
}

/* while (!terminate)
    {
        SDL_WaitEvent(&event);
        
        if (event.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            terminate = true;
        }
    } */

/*for (int i = 0; i < 5; i++)
    {
        SDL_Delay(1000);
        black_screen(renderer);
        set_next_grid(cells, next_cells, renderer);
        cp_mat(next_cells, cells);
        render_cell_grid(w, renderer, SIZE_CELL, cells);
        draw_grid(w, renderer, SIZE_CELL);
    }


    */