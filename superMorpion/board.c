#include "board.h"

subBoard * init_subBoard()
{
    //Allocation dynamique sur le tas
    subBoard * subBoard = malloc(sizeof(subBoard));

    //Initialisation des masques à 0
    subBoard->blackMask = 0ULL;
    subBoard->whiteMask = 0ULL;
    return subBoard;
}

board * init_board()
{
    //Allocation dynamique sur le tas
    board * board = malloc(sizeof(board));

    //Initialisation des sous-masques à 0
    for(int i=0;i<9;i++){
        board->listeSubBoards[i].blackMask = 0ULL;
        board->listeSubBoards[i].whiteMask = 0ULL;
    }
       


    //Initialisation des masques à 0
    board->blackMask = 0ULL;
    board->equalMask = 0ULL;
    board->whiteMask = 0ULL;

    board->prevMoves = NULL;
    return board;
}


void free_subBoard(subBoard * p)
{
    free(p);
}

void free_board(board * p)
{
    free(p);
}


void show_board(board * p)
{
    uint16_t masque_occupe = p->blackMask&p->equalMask&p->whiteMask;
    for(int j =0;j<9;j++)
    for(int i =0;i<9;i++)
    {
        int grille = i/3 + 3*(j/3);
        if(i%3 == 0 && i>0)
            printf("|");
        if((j/9)%3 == 0 && j/9 > 0)
            printf("___________");
        if(is_filled(masque_occupe,grille))
        {

            if(is_filled(p->blackMask,grille))
                printf("X");
            else if(is_filled(p->whiteMask,grille))
                printf("O");
            else
                printf("=");
        }
        else
        {
            if(is_filled(p->listeSubBoards[i].blackMask,i+9*j))
                printf("X");
            else if(is_filled(p->listeSubBoards[i].whiteMask,i+9*j))
                printf("O");
            else
                printf(" ");
        }
        if(i==8)
            printf("\n");
    }
}