#include <stdio.h>     /* printf */
#include <stdlib.h>
#include <time.h>

#include "base.h"

char board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros

char get_cell(int x, int y){
    return board[y * BOARD_SIZE + x];
}

void set_cell(int x, int y, char color){
    board[y * BOARD_SIZE + x] = color;
}

void init_board(void){
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            int rd_letter = 'A' + rand()%nb_colors;
            if(i==0 & j==BOARD_SIZE-1){
                set_cell(i, j, '^');
            }
            else if(i==BOARD_SIZE-1 & j==0){
                set_cell(i, j, 'v');
            }
            else{
                set_cell(i, j, rd_letter);
            }
        }
    }
}

void print_board(void){
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%c", get_cell(i, j));
        }
        printf("\n");
        
    }
}
