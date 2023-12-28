#ifndef MOVE
#define MOVE
#include <stdlib.h>

/**
 * Gère la mécanique des coups des joueurs
*/


/**
*Contient le numéro de la case où le joueur souhaite jouer
*Le 16e bit (bit de signe) contient la couleur du joueur
*Les blancs ont donc une valeur positive et les noirs négative
*/

typedef int move;

/**
 * Contient la pile des coups des joueurs qui sera empilée puis dépilée pour remonter dans l'arbre
 * Si le prevMove ets égal à NULL, cela signifie que l'on a atteint le premier move
*/
struct moveStack
{
    move i;
    struct moveStack * prevMove;
};
typedef struct moveStack moveStack;

/**
 * @brief  Ajoute un move en haut de la pile
 * @note   Si moveStack est NULL, initialise la pile
 * @param  moveStack: le pointeur vers la pile atcuelle
 * @param  i:   le move à ajouter
 * @retval Le pointeur vers le dernier élément de la pile
 *
*/
moveStack * addMove_top(moveStack * restrict stack, const move i);

/**
 * @brief  Ajoute le move en haut de la pile
 * @note   Même chose que pour addMove_top mais cette fois prend le pointeur du move à ajouter
 * @param  stack: 
 * @param  i: 
 * @retval 
 *
*/

moveStack * addMove_top_ptr(moveStack * restrict stack, moveStack * restrict m);

/**
 * @brief  Dépile le move
 * @note   
 * @param  stack: le pointeur vers la pile (qui sera modifié vers le nouveau dernier élément)
 * @retval renvoie le dernier move de la pile sous forme d'entier
 *
*/
move removeMove(moveStack ** restrict stack);

/**
 * @brief  Dépile le move maisrenvoie le pointeur non libéré
 * @note   Permet d'accélérer le proecessus en évitant de réalouer de la mémoire pour rien
 * @param  stack: le pointeur vers la pile (qui sera modifié vers le nouveau dernier élément)
 * @retval renvoie le dernier move de la pile sous forme d'entier
 *
*/
moveStack * removeMove_ptr(moveStack ** restrict stack);
void free_moveStack(moveStack ** restrict stack);
#endif