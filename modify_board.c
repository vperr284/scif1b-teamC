#include <stdio.h>     /* printf */
#include <stdlib.h>
#include <time.h>

#include "base.h"
#include "modify_board.h"

void update_board(char player, char chosen_color)
{
    int board_positions[BOARD_SIZE * BOARD_SIZE * 2] = { 0 };
    int c_tot = 0;
    
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if(get_cell(i, j) == player){
                board_positions[c_tot * 2] = i;
                board_positions[c_tot * 2 + 1] = j;
                c_tot++;
                }
            }
        }

    int c;
    for (c = 0; c < c_tot; c++){
        i = board_positions[c * 2];
        j = board_positions[c * 2 + 1];
        if(get_cell(i-1, j) == chosen_color & i > 0){
            board_positions[c_tot * 2] = i - 1;
            board_positions[c_tot * 2 + 1] = j;
            set_cell(board_positions[c_tot * 2], board_positions[c_tot * 2 + 1], player);
            c_tot++;
        }
        if(get_cell(i, j+1) == chosen_color & j < BOARD_SIZE - 1){
            board_positions[c_tot * 2] = i;
            board_positions[c_tot * 2 + 1] = j + 1;
            set_cell(board_positions[c_tot * 2], board_positions[c_tot * 2 + 1], player);
            c_tot++;
        }
        if(get_cell(i+1, j) == chosen_color & i < BOARD_SIZE - 1){
            board_positions[c_tot * 2] = i + 1;
            board_positions[c_tot * 2 + 1] = j;
            set_cell(board_positions[c_tot * 2], board_positions[c_tot * 2 + 1], player);
            c_tot++;
        }
        if(get_cell(i, j-1) == chosen_color & j > 0){
            board_positions[c_tot * 2] = i;
            board_positions[c_tot * 2 + 1] = j - 1;
            set_cell(board_positions[c_tot * 2], board_positions[c_tot * 2 + 1], player);
            c_tot++;
        }
    }
}

void possession(double *result_up, double *result_down)
{
    int i, j;
    double c_down = 0;
    double c_up = 0;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if(get_cell(i, j) == 'v'){
                c_down++;
            }
            else if(get_cell(i, j) == '^'){
                c_up++;
            }
        }
    }
    double perc_up = 100*c_up/(BOARD_SIZE*BOARD_SIZE);
    double perc_down = 100*c_down/(BOARD_SIZE*BOARD_SIZE);
    printf("Possession\n");
    printf("Player ^: %f\n", perc_up);
    printf("Player v: %f\n\n", perc_down);
//    utilisation de pointeurs pour récuperer les deux valeurs
    *result_up = perc_up;
    *result_down = perc_down;
}
