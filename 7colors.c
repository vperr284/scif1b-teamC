/* Template of the 7 wonders of the world of the 7 colors assigment. */

#include <stdio.h>     /* printf */
#include <stdlib.h>
#include <time.h>

/* We want a 30x30 board game by default */
#define BOARD_SIZE 5

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
//
//    int ii, jj;
//    for (ii = 0; ii < BOARD_SIZE * BOARD_SIZE; ii++) {
//        for (jj = 0; jj < 2; jj++) {
//            printf("%d", board_positions[jj * 2 + ii]);
//        }
//        printf("\n");
//    }

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

/** Program entry point */


/** Joueur aleatoire */

int joueur_alea(){

    srand((int)time(NULL));
    char lettre_alea;
    int nbr_alea=rand()%7;
    if (nbr_alea==0){
        lettre_alea='A';}
    if (nbr_alea==1){
        lettre_alea='B';}
    if (nbr_alea==2){
        lettre_alea='C';}
    if (nbr_alea==3){
        lettre_alea='D';}
    if (nbr_alea==4){
        lettre_alea='E';}
    if (nbr_alea==5){
        lettre_alea='F';}
    if (nbr_alea==6){
        lettre_alea='G';}

return lettre_alea;
}



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
    double val_up = 0, val_down = 0;
    while(val_up<=50.0 & val_down<=50.0){
        user_input = 0;
        c++;

        if(c%2 == 0){
            player = '^';
        }
        else{
            player = 'v';
        }


        if (player=='v'){
            char lettre_alea=joueur_alea();
            update_board(player,lettre_alea);
        }
        else{
            printf("Player %c must input letter\n", player);
            scanf(" %c", &user_input);
            update_board(player, user_input);
            printf("\n");
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
