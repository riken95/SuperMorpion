#ifndef MASK
#define MASK
#include <stdint.h> //Pour les uint16_t
#include <stdio.h>  //Pour écrire et lire dans des fichiers
#define WINNING_MOVES_DEST "./winning_masks.bin"


/**
 * Définit les opérations élémentaires sur les masques binaires
*/


/**
 * @brief  Permet de vérifier si oui ou non une case du masque est pleine
 * @note   
 * @param  mask: le masque binaire de 16 bits
 * @param  i: le numéro de la case
 * @retval 1 si la case est non vide, 0 sinon
 *
*/
int is_filled(uint16_t mask, int i);

/**
 * @brief  Remplit la case d'un masque
 * @note   
 * @param  mask: le masque
 * @param  i: la case à remplir
 * @retval None
 *
*/
void fill_square(uint16_t * mask, int i);
// ============== MASQUES POUR VERIFIER SI UN JOUER A GAGNE UNE GRILLE

/**
 * @brief  Lit les masques gagnants générés dans le fichier
 * @note   list sera allouée sur le tas (malloc)
 * @param  list: pointeur vers la liste à remplir avec les masques
 * @retval None
 *
*/
void read_winning_masks(uint16_t ** list);

/**
 * @brief  génère les masques pour vérifier si un joueur a gagné la grille
 * @note   enregistre les masques dans le fichier binaire qui a pour chemin WINNING_MOVES_DEST
 * @retval None
 *
*/
void generate_winning_masks();

#endif