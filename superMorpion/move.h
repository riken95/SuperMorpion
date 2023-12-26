#ifndef MOVE
#define MOVE

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
 * @brief  Ajoute un move à la pile
 * @note   Si moveStack est NULL, initialise la pile
 * @param  moveStack: le pointeur vers la pile atcuelle
 * @retval Le pointeur vers le dernier élément de la pile
 *
*/
moveStack * addMove(moveStack * stack, move i);

/**
 * @brief  Dépile le move
 * @note   
 * @param  stack: le pointeur vers la pile (qui sera modifié vers le nouveau dernier élément)
 * @retval renvoie le dernier move de la pile sous forme d'entier
 *
*/
move removeMove(moveStack ** stack);

void free_moveStack(moveStack ** stack);
#endif