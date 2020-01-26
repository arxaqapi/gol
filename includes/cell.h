#ifndef _CELL_H
#define _CELL_H

typedef struct s_cell
{
    /* data */
    int state; // 1: alive, 0: dead
    int tl_corner;
    int br_corner;
} Cell;


#endif