#include "base.h"
#include "hegemonic_player.h"
#include "random_player.h"
#include "voracious_player.h"

char hege_player(char player)
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
    
    int ard_letters_nbr[nb_colors] = { 0 };
    for(i = 0; i < nb_colors; i++){
        ard_letters_nbr[i] = 0;
    }
//    ard_letters_nbr is listing the number of letters playable around the player, as ard_letters_nbr[0] is the number of letters playable around the player after having played 'A'.
    
    int n, c;
    for(n = 0; n < nb_colors; n++){
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
                c_tot++;
            }
            if(get_cell(i, j+1) == color & j < BOARD_SIZE - 1 & not_in_table(board_positions, i, j+1)){
                board_positions[c_tot * 2] = i;
                board_positions[c_tot * 2 + 1] = j + 1;
                c_tot++;
            }
            if(get_cell(i+1, j) == color & i < BOARD_SIZE - 1 & not_in_table(board_positions, i+1, j)){
                board_positions[c_tot * 2] = i + 1;
                board_positions[c_tot * 2 + 1] = j;
                c_tot++;
            }
            if(get_cell(i, j-1) == color & j > 0 & not_in_table(board_positions, i, j-1)){
                board_positions[c_tot * 2] = i;
                board_positions[c_tot * 2 + 1] = j - 1;
                c_tot++;
            }
        }
        for(c = 0; c < c_tot; c++){
            int ii = board_positions[c * 2];
            int jj = board_positions[c * 2 + 1];
            if(((get_cell(ii-1, jj) != 'v' & get_cell(ii-1, jj) != '^') & (ii > 0)) | ((get_cell(ii, jj+1) != 'v' & get_cell(ii, jj+1) != '^') & (jj < BOARD_SIZE - 1)) | ((get_cell(ii+1, jj) != 'v' & get_cell(ii+1, jj) != '^') & (ii < BOARD_SIZE - 1)) | ((get_cell(ii, jj-1) != 'v' & get_cell(ii, jj-1) != '^') & (jj > 0))){
                    ard_letters_nbr[n]++;
            }
        }
        save_board_positions(board_positions, board_positions_copy);
        c_tot = c_tot_copy;
    }
    
    c = 0;
    int c_same = 0;
    int max = ard_letters_nbr[c];
    for(i = 0; i < nb_colors; i++){
//        printf("%d", ard_letters_nbr[i]);
        if(max < ard_letters_nbr[i]){
            max = ard_letters_nbr[i];
            c = i;
        }
        else if(max == ard_letters_nbr[i]){
            c_same++;
        }
//        printf("\n");
    }
    
    int same = 0;
//    boolean true if all letters have the same ard_letters_nbr
    if(c_same == nb_colors){
        same = 1;
    }
    
//    in case of surrounded letter
    if(same){
        i = 0;
        j = 0;
        for(i = 0; i < BOARD_SIZE; i++){
            for(j = 0; j < BOARD_SIZE; j++){
                if((get_cell(i, j) != '^') | (get_cell(i, j) != 'v')){
                    if((get_cell(i-1, j) == player & i > 0) & (get_cell(i, j+1) == player & j < BOARD_SIZE - 1) & (get_cell(i+1, j) == player & i < BOARD_SIZE - 1) & (get_cell(i, j-1) == player & j > 0)){
                        return rd_player(player);
                    }
                }
            }
        }
    }
//    printf("\n%c\n", 'A' + c);
    return 'A' + c;
}
