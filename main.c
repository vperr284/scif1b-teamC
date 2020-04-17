#include <stdio.h>     /* printf */
#include <stdlib.h>
#include <time.h>

#include "base.h"
#include "modify_board.h"
#include "random_player.h"
#include "voracious_player.h"

int main(void)
{
    srand((unsigned)time(NULL)); // initialisation of rand
    
    int game_mode = 0;
    printf("\nSelect game mode\n");
    printf("****CLASSIC****\n");
    printf("1: Player vs Player\n");
    printf("2: Player vs rAIndom\n");
    printf("3: Player vs vorAIcious\n");
    printf("4: rAIndom vs vorAIcious\n");
    printf("****TOURNAMENT****\n");
    printf("5: rAIndom vs vorAIcious\n");
    scanf("%d", &game_mode);
    
    printf("\n\nWelcome to the %d wonders of the world of the %d colors\n"
       "*****************************************************\n\n"
       , nb_colors, nb_colors);
    
    char player;
    if(game_mode < 5){
        printf("Current board state:\n");
        init_board();
        print_board();
        char user_input = 0;
        int c = 0;
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
                    case 3:
                        if(c%2 == 0){
                            char voracious_letter = voracious_player('^');
                            update_board('^', voracious_letter);
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
                    case 4:
                        if(c%2 == 0){
                            char voracious_letter = voracious_player('^');
                            update_board('^', voracious_letter);
                            printf("\n");
                        }
                        else{
                            char rd_letter = rd_player('v');
                            update_board('v', rd_letter);
                            printf("\n");
                        }
                        break;
                }
                
                printf("Current board state:\n");
                print_board();
                printf("\n");
                possession(&val_up, &val_down);
        //        val_up et val_down are wanted results
                printf("Possession\n");
                printf("Player ^: %f\n", val_up);
                printf("Player v: %f\n\n", val_down);
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
    else{
        int match;
        
        int scores[3] = { 0 }; //^vd
        int ind;
        for(ind = 0; ind < 3; ind++){
            scores[ind] = 0;
    }
        switch(game_mode){
            case 5:
                for(match = 1; match < 101; match++){
                    init_board();
//                    printf("Current board state:\n");
//                    print_board();
//                    printf("\n");
                    int c = 0;
                    double val_up = 0, val_down = 0;
                    char voracious_letter, rd_letter;
                    while(val_up<=50.0 & val_down<=50.0){
                        c++;
                        if(c%2 == 0){
                            voracious_letter = voracious_player('^');
                            update_board('^', voracious_letter);
                        }
                        else{
                            rd_letter = rd_player('v');
                            update_board('v', rd_letter);
                        }
//                        printf("Current board state:\n");
//                        print_board();
//                        printf("\n");
                        possession(&val_up, &val_down);
//                        val_up et val_down are wanted results
//                        printf("Possession\n");
//                        printf("Player ^: %f\n", val_up);
//                        printf("Player v: %f\n\n", val_down);
                    }
                    if(val_up>val_down){
                        scores[0] = scores[0] + 1;
                    }
                    else if(val_down>val_up){
                        scores[1] = scores[1] + 1;
                    }
                    else{
                        scores[2] = scores[2] + 1;
                    }
                    printf("Match %d | %d %d %d\n", match, scores[0], scores[1], scores[2]);
                }
                int winner_ind = 0;
                int max = scores[winner_ind];
                for(ind = 0; ind < 3; ind++){
                    if(max < scores[ind]){
                        max = scores[ind];
                        winner_ind = ind;
                    }
                }
                if(winner_ind == 0){
                    printf("\nAnd the winner of the tournament is........\n\n\n\nvorAIcious with %d matches won!\n", max);
                }
                else if(winner_ind == 1){
                    printf("\nAnd the winner of the tournament is........\n\n\n\nrAIndom with %d matches won!\n", max);
                }
                else{
                    printf("\nAnd the winner of the tournament is........\n\n\n\nNO ONE \n\nLOL\n");
                }
                
                return 0; // Everything went well
        }
    }
    return 9; //impossible
}
