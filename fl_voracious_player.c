#include "base.h"
#include "fl_voracious_player.h"
#include "voracious_player.h"
   
char fl_v_player(char player)
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
    
    int letters_nbr[nb_colors * nb_colors] = { 0 };
    for(i = 0; i < nb_colors; i++){
        for(j = 0; j < nb_colors; j++){
            letters_nbr[i * nb_colors + j] = 0;
        }
    }
    
//    initial save of board_positions and c_tot
    int board_positions_i[BOARD_SIZE * BOARD_SIZE * 2] = { 0 };
    save_board_positions(board_positions_i, board_positions);
    int c_tot_i = c_tot;

    int n1, n2, c;
    for(n1 = 0; n1 < nb_colors; n1++){
        save_board_positions(board_positions, board_positions_i);
        int c_tot = c_tot_i;
        
        char color1 = 'A' + n1;
        for(c = 0; c < c_tot; c++){
            i = board_positions[c * 2];
            j = board_positions[c * 2 + 1];
            int ii;
            if(get_cell(i-1, j) == color1 & i > 0 & not_in_table(board_positions, i-1, j)){
                board_positions[c_tot * 2] = i - 1;
                board_positions[c_tot * 2 + 1] = j;
                for(ii = 0; ii < nb_colors; ii++){
                    letters_nbr[n1 * nb_colors + ii]++;
                }
                c_tot++;
            }
            if(get_cell(i, j+1) == color1 & j < BOARD_SIZE - 1 & not_in_table(board_positions, i, j+1)){
                board_positions[c_tot * 2] = i;
                board_positions[c_tot * 2 + 1] = j + 1;
                for(ii = 0; ii < nb_colors; ii++){
                    letters_nbr[n1 * nb_colors + ii]++;
                }
                c_tot++;
            }
            if(get_cell(i+1, j) == color1 & i < BOARD_SIZE - 1 & not_in_table(board_positions, i+1, j)){
                board_positions[c_tot * 2] = i + 1;
                board_positions[c_tot * 2 + 1] = j;
                for(ii = 0; ii < nb_colors; ii++){
                    letters_nbr[n1 * nb_colors + ii]++;
                }
                c_tot++;
            }
            if(get_cell(i, j-1) == color1 & j > 0 & not_in_table(board_positions, i, j-1)){
                board_positions[c_tot * 2] = i;
                board_positions[c_tot * 2 + 1] = j - 1;
                for(ii = 0; ii < nb_colors; ii++){
                    letters_nbr[n1 * nb_colors + ii]++;
                }
                c_tot++;
            }
        }
        
//        save for each first letter played
        int board_positions_copy[BOARD_SIZE * BOARD_SIZE * 2] = { 0 };
        save_board_positions(board_positions_copy, board_positions);
        int c_tot_copy = c_tot;
        
        for(n2 = 0; n2 < nb_colors; n2++){
            char color2 = 'A' + n2;
            save_board_positions(board_positions, board_positions_copy);
            c_tot = c_tot_copy;
            for(c = 0; c < c_tot; c++){
                i = board_positions[c * 2];
                j = board_positions[c * 2 + 1];
                if(get_cell(i-1, j) == color2 & i > 0 & not_in_table(board_positions, i-1, j)){
                    board_positions[c_tot * 2] = i - 1;
                    board_positions[c_tot * 2 + 1] = j;
                    letters_nbr[n1 * nb_colors + n2]++;
                    c_tot++;
                }
                if(get_cell(i, j+1) == color2 & j < BOARD_SIZE - 1 & not_in_table(board_positions, i, j+1)){
                    board_positions[c_tot * 2] = i;
                    board_positions[c_tot * 2 + 1] = j + 1;
                    letters_nbr[n1 * nb_colors + n2]++;
                    c_tot++;
                }
                if(get_cell(i+1, j) == color2 & i < BOARD_SIZE - 1 & not_in_table(board_positions, i+1, j)){
                    board_positions[c_tot * 2] = i + 1;
                    board_positions[c_tot * 2 + 1] = j;
                    letters_nbr[n1 * nb_colors + n2]++;
                    c_tot++;
                }
                if(get_cell(i, j-1) == color2 & j > 0 & not_in_table(board_positions, i, j-1)){
                    board_positions[c_tot * 2] = i;
                    board_positions[c_tot * 2 + 1] = j - 1;
                    letters_nbr[n1 * nb_colors + n2]++;
                    c_tot++;
                }
            }
        }
    }
    
//    complexite en nb_colors * nb_colors, pour faire de meme avec n prochains coups, il faudrait n boucles imbriquees peut-etre avec un programme recursif?
    
    int c_i = 0, c_j = 0;
    int max = letters_nbr[0];
    for(i = 0; i < nb_colors; i++){
        for(j = 0; j < nb_colors; j++){
            if(max < letters_nbr[i * nb_colors + j]){
                max = letters_nbr[i * nb_colors + j];
                c_i = i;
                c_j = j;
            }
        }
    }
    
//    for(i = 0; i < nb_colors; i++){
//        for(j = 0; j < nb_colors; j++){
//            printf("%d ", letters_nbr[i * nb_colors + j]);
//        }
//        printf("\n");
//    }
//    
//    printf("%d%d\n", c_i, c_j);

    return 'A' + c_i;
}
