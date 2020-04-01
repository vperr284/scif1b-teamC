#include <stdio.h>     /* printf */
#include <stdlib.h>
#include <time.h>

#include "base.h"
#include "modify_board.h"
#include "random_player.h"

void print_board(void)
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%c", get_cell(i, j));
        }
        printf("\n");
        
    }
}

// old update_board (too many calculus)
//void update_board(char player, char chosen_color)
//{
//    int c = 0;
//    do{
//        c = 0;
//        int i, j;
//        for (i = 0; i < BOARD_SIZE; i++) {
//            for (j = 0; j < BOARD_SIZE; j++) {
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

int main(void)
{
    srand((unsigned)time(NULL)); // initialisation of rand
    
    int game_mode = 0;
    printf("\nSelect game mode\n");
    printf("1: Player vs Player\n");
    printf("2: Player vs AI\n");
    scanf("%d", &game_mode);
    
    init_board();
    printf("\n\nWelcome to the %d wonders of the world of the %d colors\n"
       "*****************************************************\n\n"
       "Current board state:\n", nb_colors, nb_colors);
    print_board();
    
//    update_board('v','A');
//
//    printf("Current board state:\n");
//    print_board();
    
    
    char user_input = 0;
    int c = 0;
    char player;
    double val_up = 0, val_down = 0;
    while(val_up<=50.0 & val_down<=50.0){
        user_input = 0;
        c++;
        
        switch(game_mode){
            case 1:
                if(c%2 == 0){
                    player = '^';
                }
                else{
                    player = 'v';
                }
                scanf(" %c", &user_input);
                while (user_input == '^' | user_input == 'v'){
                    scanf(" %c", &user_input);
                }
                update_board(player, user_input);
                printf("\n");
                break;
            case 2:
                if(c%2 == 0){
                    char rd_letter = rd_player('^');
                    printf("rd %c", rd_letter);
                    update_board('^', rd_letter);
                    printf("\n");
                }
                else{
                    printf("Player v must input letter\n");
                    scanf(" %c", &user_input);
                    while (user_input == '^' | user_input == 'v'){
                        scanf(" %c", &user_input);
                    }
                    update_board('v', user_input);
                    printf("\n");
                }
                break;
        }
        
        printf("Current board state:\n");
        print_board();
        printf("\n");
        possession(&val_up, &val_down);
//        val_up et val_down contiennent les résultats voulus
    }
    
    if(val_up>val_down){
        printf("****** Player ^ won! ******\n");
    }
    else if(val_down>val_up){
        printf("****** Player v won! ******\n");
    }
    else{
        printf("****** Draw ******\n");
    }
    
    return 0; // Everything went well
}
