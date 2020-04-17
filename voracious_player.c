#include <stdio.h>     /* printf */
#include <stdlib.h>
#include <time.h>

#include "base.h"
#include "voracious_player.h"


void save_board_positions(int *tab1, int *tab2)
{
    int i,j;
    for(i = 0; i < BOARD_SIZE * BOARD_SIZE; i++){
        for(j = 0; j < 2; j++){
            tab1[i * 2 + j] = tab2[i * 2 + j];
        }
    }
}

int not_in_table(int *tab, int i0, int j0)
{
    int i;
    for(i = 0; i < BOARD_SIZE * BOARD_SIZE; i++){
            if (tab[i * 2] == i0 & tab[i * 2 + 1] == j0){
                return 0;
            }
    }
    return 1;
}
               
char voracious_player(char player)
{
    int board_positions[BOARD_SIZE * BOARD_SIZE * 2] = { 0 };
    int c_tot = 0;
    
    int i, j;
    for(i = 0; i < BOARD_SIZE; i++){
        for(j = 0; j < BOARD_SIZE; j++){
            if(get_cell(i, j) == player){
                board_positions[c_tot * 2] = i;
                board_positions[c_tot * 2 + 1] = j;
                c_tot++;
                }
            }
        }
    
    int letters_nbr[nb_colors] = { 0 };
    for(i = 0; i < nb_colors; i++){
        letters_nbr[i] = 0;
    }
    
    int n, c;
    for(n = 0; n<nb_colors; n++){
        char color = 'A' + n;
        int board_positions_copy[BOARD_SIZE * BOARD_SIZE * 2] = { 0 };
        save_board_positions(board_positions_copy, board_positions);
        int c_tot_copy = c_tot;
        for(c = 0; c < c_tot; c++){
            i = board_positions[c * 2];
            j = board_positions[c * 2 + 1];
            if(get_cell(i-1, j) == color & i > 0 & not_in_table(board_positions, i-1, j)){
                board_positions[c_tot * 2] = i - 1;
                board_positions[c_tot * 2 + 1] = j;
                letters_nbr[get_cell(i-1, j) - 'A'] = letters_nbr[get_cell(i-1, j) - 'A'] + 1;
            }
            if(get_cell(i, j+1) == color & j < BOARD_SIZE - 1 & not_in_table(board_positions, i, j+1)){
                board_positions[c_tot * 2] = i;
                board_positions[c_tot * 2 + 1] = j + 1;
                letters_nbr[get_cell(i, j+1) - 'A'] = letters_nbr[get_cell(i, j+1) - 'A'] + 1;
                c_tot++;
            }
            if(get_cell(i+1, j) == color & i < BOARD_SIZE - 1 & not_in_table(board_positions, i+1, j)){
                board_positions[c_tot * 2] = i + 1;
                board_positions[c_tot * 2 + 1] = j;
                letters_nbr[get_cell(i+1, j) - 'A'] = letters_nbr[get_cell(i+1, j) - 'A'] + 1;
                c_tot++;
            }
            if(get_cell(i, j-1) == color & j > 0 & not_in_table(board_positions, i, j-1)){
                board_positions[c_tot * 2] = i;
                board_positions[c_tot * 2 + 1] = j - 1;
                letters_nbr[get_cell(i, j-1) - 'A'] = letters_nbr[get_cell(i, j-1) - 'A'] + 1;
                c_tot++;
            }
        }
        save_board_positions(board_positions, board_positions_copy);
        c_tot = c_tot_copy;
    }
    c = 0;
    int max = letters_nbr[c];
    for(i = 0; i < nb_colors; i++){
        if(max < letters_nbr[i]){
            max = letters_nbr[i];
            c = i;
        }
    }
    return 'A' + c;
}
