#include <stdio.h>     /* printf */
#include <stdlib.h>
#include <time.h>

#include "base.h"
#include "random_player.h"

char rd_player(char player)
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

    char letters_near[nb_colors] = { '0' };
    for(i = 0; i < nb_colors; i++){
        letters_near[i] = '0';
    }
    int c;
    for(c = 0; c < c_tot; c++){
        i = board_positions[c * 2];
        j = board_positions[c * 2 + 1];
        if(i > 0 & get_cell(i-1, j) != 'v' & get_cell(i-1, j) != '^'){
            letters_near[get_cell(i-1, j) - 'A'] = get_cell(i-1, j);
        }
        if(j < BOARD_SIZE - 1 & get_cell(i, j+1) != 'v' & get_cell(i, j+1) != '^'){
            letters_near[get_cell(i, j+1) - 'A'] = get_cell(i, j+1);
        }
        if(i < BOARD_SIZE - 1 & get_cell(i+1, j) != 'v' & get_cell(i+1, j) != '^'){
            letters_near[get_cell(i+1, j) - 'A'] = get_cell(i+1, j);
        }
        if(j > 0 & get_cell(i, j-1) != 'v' & get_cell(i, j-1) != '^'){
            letters_near[get_cell(i, j-1) - 'A'] = get_cell(i, j-1);
        }
    }
    
    int boo = 0;
    for(i = 0; i < nb_colors; i++){
        if(letters_near[i] != '0'){
            boo = 1;
        }
    }
    if(boo == 1){
        int rd_number = rand()%nb_colors;
        while (letters_near[rd_number] == '0'){
            rd_number = rand()%nb_colors;
        }
        return letters_near[rd_number];
    }
    else{
        return 'A';
    }
}
