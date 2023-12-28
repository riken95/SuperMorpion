#ifndef MASK
#define MASK
#include <stdint.h> //Pour les uint16_t
#include <stdio.h>  //Pour écrire et lire dans des fichiers
#include <stdlib.h> //Pour les malloc
#define WINNING_MOVES_DEST "./winning_masks.bin"




// ===================== Macros (plus rapides qu'une fonction standard)

/**
 * @brief  Permet de vérifier si oui ou non une case du masque est pleine
 * @note   
 * @param  mask: le masque binaire de 16 bits
 * @param  i: le numéro de la case
 * @retval 1 si la case est non vide, 0 sinon
 *
*/
#define is_filled(mask, i) ((mask) & (1ULL<<(i)))




/**
 * Définit les opérations élémentaires sur les masques binaires
*/




/**
 * @brief  Remplit la case d'un masque
 * @note   
 * @param  mask: le masque
 * @param  i: la case à remplir
 * @retval None
 *
*/

#define fill_square(mask, i)   ( *(mask) |=  1ULL<<(i))

/**
 * @brief  Met à 0 le bit souhaité
 * @note   
 * @retval 
 *
*/
#define empty_square(mask, i)    (*(mask) &= ~(1ULL<<(i)))



// ============== MASQUES POUR VERIFIER SI UN JOUER A GAGNE UNE GRILLE

/**
 * @brief  Lit les masques gagnants générés dans le fichier
 * @note   list sera allouée sur le tas (malloc)
 * @param  list: pointeur vers la liste à remplir avec les masques
 * @param  taille: pointeur vers la taille du tableau de retour
 * @retval None
 *
*/
void read_winning_masks(uint16_t ** restrict list, int * restrict taille);

/**
 * @brief  génère les masques pour vérifier si un joueur a gagné la grille
 * @note   enregistre les masques dans le fichier binaire qui a pour chemin WINNING_MOVES_DEST
 * @retval None
 *
*/
void generate_winning_masks();

/**
 * @brief Affiche le masque binaire uint16_t 
 * @note   
 * @param  mask: 
 * @retval None
 *
*/
void show_mask(const uint16_t mask);


#endif