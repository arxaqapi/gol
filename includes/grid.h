#ifndef _GRID_H
#define _GRID_H

#include <SDL2/SDL.h>
#include <assert.h>
#include <stdbool.h>

#define W_WIDTH 400
#define W_HEIGTH 300
#define SIZE_CELL 20
#define EXIT_ERROR -1


int le_vrai_modulo(int a, int b);
int **create_mat_int(int cell_size);
int **init_grid_rand(int cell_size);
void flip_cell(int x, int y, SDL_Renderer *r, int offset, bool nextState);
void render_cell_grid(SDL_Window *w, SDL_Renderer *r, int cell_size, int **cells);
void print_mat(int **mat, int cell_size);
void draw_grid(SDL_Window *w, SDL_Renderer *r, int cell_size);
int count_neighbours(int **cells, int x, int y);
void set_next_grid(int **cells, int **next_cells, SDL_Renderer *r);
void black_screen(SDL_Renderer *r);
void cp_mat(int **source, int **dest);


#endif