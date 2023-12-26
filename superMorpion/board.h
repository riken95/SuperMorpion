#ifndef BOARD
#define BOARD
#include "mask.h"
#include "move.h"

/*
* Définit le plateau de jeu
* 
* Les "Mask" sont des masques binaires.
* Chaque bit égal à 1 signifie que la case est non vide
* */


struct subBoard
{
    uint16_t blackMask; //Les coups blancs
    uint16_t whiteMask; //Les coups noirs
};

typedef struct subBoard subBoard;

struct board
{
    subBoard listeSubBoards[9];
    uint16_t blackMask; //Les sous-grilles gagnées par les blancs
    uint16_t whiteMask; //Les sous-grilles gagnées par les noirs
    uint16_t equalMask; //Les sous-grilles pù il y a match nul
    moveStack * prevMoves;
};

typedef struct board board;

/**
 * @brief  Initialise le subBoard
 * @note   toutes les cases sont vides à l'initialisation
 * @retval le pointeur vers le subBoard (alloué sur le tas)
 *
*/
subBoard * init_subBoard();

/**
 * @brief  Initialise le board
 * @note   les suboard sont initialisés, toutes les cases sont vides
 * @retval le pointeur vers le board (alloué sur la pile)
 *
*/
board * init_board();

/**
 * @brief  Affiche le plateau
 * @note   
 * @param  p: 
 * @retval None
 *
*/
void show_board(board * p);


/**
 * @brief  Libère l'espace en mémoire du subBoard
 * @note   
 * @retval None
 *
*/
void free_subBoard(subBoard * p);

/**
 * @brief  Libère l'espace en mémoire des subBoards et du board
 * @note   
 * @retval None
 *
*/
void free_board(board * p);

#endif