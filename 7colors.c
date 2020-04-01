#include <stdio.h>     /* printf */
#include <stdlib.h>
#include <time.h>

/* We want a BOARD_SIZExBOARD_SIZE board game by default */
#define BOARD_SIZE 5

char board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros

char get_cell(int x, int y)
{
    return board[y * BOARD_SIZE + x];
}

void set_cell(int x, int y, char color)
{
    board[y * BOARD_SIZE + x] = color;
}

void init_board(void)
{
    srand((int)time(NULL)); // initialisation of rand
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            int rd_number = rand()%7;
            if(i==0 & j==BOARD_SIZE-1){
                set_cell(i, j, '^');
            }
            else if(i==BOARD_SIZE-1 & j==0){
                set_cell(i, j, 'v');
            }
            else{
                switch(rd_number){
                    case 0:
                        set_cell(i, j, 'A');
                        break;
                    case 1:
                        set_cell(i, j, 'B');
                        break;
                    case 2:
                        set_cell(i, j, 'C');
                        break;
                    case 3:
                        set_cell(i, j, 'D');
                        break;
                    case 4:
                        set_cell(i, j, 'E');
                        break;
                    case 5:
                        set_cell(i, j, 'F');
                        break;
                    case 6:
                        set_cell(i, j, 'G');
                        break;
                }
            }
        }
    }
}

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
    char letters_near[7] = { '0' };
    int i;
    for (i = 0; i < 7; i++){
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
    
    int rd_number = rand()%7;
    while (letters_near[rd_number] == '0'){
        rd_number = rand()%7;
    }
    return letters_near[rd_number];
}


int main(void)
{
    int game_mode = 0;
    printf("\nSelect game mode\n");
    printf("1: Player vs Player\n");
    printf("2: Player vs AI\n");
    scanf("%d", &game_mode);
    
    init_board();
    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
       "*****************************************************\n\n"
       "Current board state:\n");
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
