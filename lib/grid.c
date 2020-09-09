#include "grid.h"

int le_vrai_modulo(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

int **create_mat_int(int cell_size)
{
    int **grid = malloc(W_HEIGTH / cell_size * sizeof(int *));
    if (grid == NULL)
    {
        printf("Problème d'allocation init_grid !");
        exit(1);
    }
    for (int i = 0; i < W_HEIGTH / cell_size; i++)
    {
        grid[i] = malloc(W_WIDTH / cell_size * sizeof(int));
        if (grid[i] == NULL)
        {
            printf("Problème d'allocation init_grid !");
            exit(1);
        }
    }
    return grid;
}

int **init_grid_rand(int cell_size)
{
    /// \brief init grid with random numbers
    int **grid = create_mat_int(cell_size);
    int rand_n;
    for (int i = 0; i < W_HEIGTH / cell_size; i++)
    {
        for (int j = 0; j < W_WIDTH / cell_size; j++)
        {
            grid[i][j] = rand() % 2;
        }
    }
    return grid;
}

void free_grid(int **grid, int cell_size)
{
    for (int i = 0; i < W_HEIGTH / cell_size; i++)
    {
        free(grid[i]);
    }
    free(grid);
}

void flip_cell(int x, int y, SDL_Renderer *r, int offset, bool nextState)
{
    int grid_offset = 1;
    SDL_Rect rect = {x + grid_offset, y + grid_offset, offset - (grid_offset * 2), offset - (grid_offset * 2)};

    // SDL_Rect rect = {x, y, y + offset, x + offset};

    SDL_Color col = {255, 255, 255, 255};

    if (nextState) // alive
    {
        col.r = 0;
        col.g = 0;
        col.b = 0;
    }

    SDL_SetRenderDrawColor(r, col.r, col.g, col.b, col.a);
    SDL_RenderFillRect(r, &rect);
}

void render_cell_grid(SDL_Window *w, SDL_Renderer *r, int cell_size, int **cells)
{
    /// \brief from renderer to screen
    for (int i = 0; i < (W_HEIGTH / cell_size); i++)
    {
        for (int j = 0; j < (W_WIDTH / cell_size); j++)
        {
            /* if (cells[i][j] == 1)
            {
                //  revive
                flip_cell(j * cell_size, i * cell_size, r, cell_size, true);
            }
            if (cells[i][j] == 0)
            {
                //  kill
                flip_cell(j * cell_size, i * cell_size, r, cell_size, false);
            } */

            flip_cell(j * cell_size, i * cell_size, r, cell_size, cells[i][j]? true : false);

        }
    }
    SDL_RenderPresent(r);
}

void print_mat(int **mat, int cell_size)
{
    for (int i = 0; i < W_HEIGTH / cell_size; i++)
    {
        for (int j = 0; j < W_WIDTH / cell_size; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}


int count_neighbours(int **cells, int x, int y)
{
    int nb_r = W_HEIGTH / SIZE_CELL;
    int nb_c = W_WIDTH / SIZE_CELL;
    int sum = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (!(i == 0 && j == 0))
            {
                /* printf("x: %d | y: %d", x+i, y+j); */
                sum += cells[le_vrai_modulo(x + i, nb_r)][le_vrai_modulo(y + j, nb_c)];
            }
        }
    }
    return sum; //(int)rand()%4;
}

void set_next_grid(int **cells, int **next_cells, SDL_Renderer *r)
{
    /// \brief set next_cells to next itération
    int c_nb = 0;
    for (int i = 0; i < W_HEIGTH / SIZE_CELL; i++)
    {
        for (int j = 0; j < W_WIDTH / SIZE_CELL; j++)
        {
            c_nb = count_neighbours(cells, i, j);
            if (cells[i][j] == 1 && c_nb < 2)
            {
                //  Kill cell, underpopulation
                next_cells[i][j] = 0;
            }
            else if (cells[i][j] == 1 && c_nb > 3)
            {
                //  Kill Cell, overpopulation
                next_cells[i][j] = 0;
            }
            else if (cells[i][j] == 0 && c_nb == 3)
            {
                //  Revive cell, reproduction
                next_cells[i][j] = 1;
            }
            else
            {
                next_cells[i][j] = cells[i][j];
            }
        }
    }
}

void black_screen(SDL_Renderer *r)
{
    SDL_Color bl = {0, 0, 0, 255};
    SDL_SetRenderDrawColor(r, bl.r, bl.g, bl.b, bl.a);
    SDL_RenderClear(r);
    SDL_RenderPresent(r);
}

void copy_mat(int **source, int **dest)
{
    for (int i = 0; i < W_HEIGTH / SIZE_CELL; i++)
    {
        for (int j = 0; j < W_WIDTH / SIZE_CELL; j++)
        {
            dest[i][j] = source[i][j];
        }
    }
}