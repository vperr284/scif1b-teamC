/* Template of the 7 wonders of the world of the 7 colors assigment. */

#include <stdio.h>     /* printf */
#include <stdlib.h>
#include <time.h>

/* We want a 30x30 board game by default */
#define BOARD_SIZE 15

/** Represent the actual current board game
 *
 * NOTE: global variables are usually discouraged (plus encapsulation in
 *     an appropriate data structure would also be preferred), but don't worry.
 *     For this first assignment, no dinosaure will get you if you do that.
 */
char board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros

/** Retrieves the color of a given board cell */
char get_cell(int x, int y)
{
    return board[y * BOARD_SIZE + x];
}

/** Changes the color of a given board cell */
void set_cell(int x, int y, char color)
{
    board[y * BOARD_SIZE + x] = color;
}

/** Prints the current state of the board on screen
 *
 * Implementation note: It would be nicer to do this with ncurse or even
 * SDL/allegro, but this is not really the purpose of this assignment.
 */

void init_board(void)
{
    srand((int)time(NULL)); // initialisation of rand
    int nombre_aleatoire = 0;
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            nombre_aleatoire = rand()%7;
            //printf("%d",nombre_aleatoire);
            if(i==0 & j==BOARD_SIZE-1){
                set_cell(i, j, '^');
            }
            else if(i==BOARD_SIZE-1 & j==0){
                set_cell(i, j, 'v');
            }
            else{
                switch(nombre_aleatoire){
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

void update_board(char player, char chosen_color)
{
    int c = 0;
    do{
        c = 0;
        int i, j;
        for (i = 0; i < BOARD_SIZE; i++) {
            for (j = 0; j < BOARD_SIZE; j++) {
                if(get_cell(i, j) == chosen_color){
                    if((get_cell(i-1, j) == player & i > 0) | (get_cell(i, j+1) == player & j < BOARD_SIZE - 1) | (get_cell(i+1, j) == player & i < BOARD_SIZE - 1) | (get_cell(i, j-1) == player & j > 0)){
                        set_cell(i, j, player);
                        c++;
                    }
                }
            }
        }
    } while(c != 0);
}

void possession(void)
{
    int i, j;
    double c_bas = 0;
    double c_haut = 0;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if(get_cell(i, j) == 'v'){
                c_bas++;
            }
            else if(get_cell(i, j) == '^'){
                c_haut++;
            }
        }
    }
    double perc_haut = 100*c_haut/(BOARD_SIZE*BOARD_SIZE);
    double perc_bas = 100*c_bas/(BOARD_SIZE*BOARD_SIZE);
    printf("Possession\n");
    printf("Player ^: %f\n", perc_haut);
    printf("Player v: %f\n\n", perc_bas);
}

//void update_board(char player, char chosen_color)
//{
//    int c = 0;
//    if(player == 'v'){
//        do{
//            c = 0;
//            int i, j;
//            if(get_cell(i-1, j) == player & i > 0){
//
//            }
//            else if(get_cell(i, j+1) == player & j < BOARD_SIZE - 1){
//
//            }
//            else if(get_cell(i+1, j) == player & i < BOARD_SIZE - 1){
//
//            }
//            else if(get_cell(i, j-1) == player & j > 0){
//
//            }
//        } while(c != 0);
//    }
//    else if(player == '^'){
//        do{
//            c = 0;
//            int i, j;
//            for (i = 0; i < BOARD_SIZE; i++) {
//                for (j = 0; j < BOARD_SIZE; j++) {
//                    if(get_cell(i, j) == chosen_color){
//                        if((get_cell(i-1, j) == player & i > 0) | (get_cell(i, j+1) == player & j < BOARD_SIZE - 1) | (get_cell(i+1, j) == player & i < BOARD_SIZE - 1) | (get_cell(i, j-1) == player & j > 0)){
//                            set_cell(i, j, 'v');
//                            c++;
//                        }
//                    }
//                }
//            }
//        } while(c != 0);
//    }
//
//}

/** Program entry point */

int main(void)
{
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
    int c=0;
    char player;
    while(user_input != 'q'){
        user_input = 0;
        c++;
        
        if(c%2 == 0){
            player = '^';
        }
        else{
            player = 'v';
        }
        
        printf("Player %c must input letter\n", player);
        scanf(" %c", &user_input);
        update_board(player, user_input);
        printf("\n");
        
        printf("Current board state:\n");
        print_board();
        printf("\n");
        possession();
        

    }
    
    return 0; // Everything went well
}
