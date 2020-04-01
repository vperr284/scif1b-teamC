#ifndef base_h
#define base_h

#include <stdio.h>

/* We want a BOARD_SIZExBOARD_SIZE board game by default */
#define BOARD_SIZE 5
#define nb_colors 7

char get_cell(int x, int y);
void set_cell(int x, int y, char color);
void init_board(void);

#endif /* base_h */
