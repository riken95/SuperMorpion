#ifndef PROGRAM
#define PROGRAM
#include "board.h"
#define MAX_EVAL 10000

/**
 * @brief  La fonction d'évaluation
 * @note   
 * @param  b: Le plateau de jeu
 * @retval L'évaluation de la position
 *
*/
int eval(const board * restrict b);


/**
 * @brief  La fonction de recherche
 * @note   
 * @param  alpha: 
 * @param  beta:
 * @param  depth:  La profondeur restante à explorer
 * @param  b:   Le plateau de jeu
 * @param  list_winning_masks: Sert à détecter les grilles terminées
 * @param  taille_liste: //
 * @retval 
 *
*/
int min_max_search(int alpha, int beta, const int depth, board * restrict b,
const uint16_t * restrict list_winning_masks, const int taille_liste);


int computer_play(board * restrict b,const int max_depth, const uint16_t * restrict list_winning_masks, const int taille_liste);

#endif