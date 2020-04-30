#include "base.h"
#include "modify_board.h"

// old update_board (too many calculus)
//void update_board(char player, char chosen_color)
//{
//    int c = 0;
//    do{
//        c = 0;
//        int i, j;
//        for(i = 0; i < BOARD_SIZE; i++){
//            for(j = 0; j < BOARD_SIZE; j++){
//                if(get_cell(i, j) == chosen_color){
//                    if((get_cell(i-1, j) == player & i > 0) | (get_cell(i, j+1) == player & j < BOARD_SIZE - 1) | (get_cell(i+1, j) == player & i < BOARD_SIZE - 1) | (get_cell(i, j-1) == player & j > 0)){
//                        set_cell(i, j, player);
//                        c++;
//                    }
//                }
//            }
//        }
//    } while(!c);
//}

void update_board(char player, char chosen_color)
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

    int c;
    for(c = 0; c < c_tot; c++){
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
    for(i = 0; i < BOARD_SIZE; i++){
        for(j = 0; j < BOARD_SIZE; j++){
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
//    use of pointers to get two values
    *result_up = perc_up;
    *result_down = perc_down;
}
