#include <stdio.h>     /* printf */
#include <stdlib.h>
#include <time.h>

#include "base.h"
#include "random_player.h"

void switch_letters_near(char *letters_near, int i, int j){
    switch(get_cell(i, j)){
        case 'A':
            letters_near[0] = 'A';
            break;
        case 'B':
            letters_near[1] = 'B';
            break;
        case 'C':
            letters_near[2] = 'C';
            break;
        case 'D':
            letters_near[3] = 'D';
            break;
        case 'E':
            letters_near[4] = 'E';
            break;
        case 'F':
            letters_near[5] = 'F';
            break;
        case 'G':
            letters_near[6] = 'G';
            break;
        case '^':
            break;
        case 'v':
            break;
    }
}

char rd_player(char player){
    char letters_near[nb_colors] = { '0' };
    int i;
    for (i = 0; i < nb_colors; i++){
        letters_near[i] = '0';
    }

    int board_positions[BOARD_SIZE * BOARD_SIZE * 2] = { 0 };
    int c_tot = 0;

    int j;
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
        if(i > 0){
            switch_letters_near(letters_near, i-1, j);
        }
        if(j < BOARD_SIZE - 1){
            switch_letters_near(letters_near, i, j+1);
        }
        if(i < BOARD_SIZE - 1){
            switch_letters_near(letters_near, i+1, j);
        }
        if(j > 0){
            switch_letters_near(letters_near, i, j-1);
        }
    }
    
    int rd_number = rand()%nb_colors;
    while (letters_near[rd_number] == '0'){
        rd_number = rand()%nb_colors;
    }
    return letters_near[rd_number];
}
