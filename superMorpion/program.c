#include "program.h"


int eval(const board * restrict b)
{
    if(b->winner>-2)//La partie est terminée
        return MAX_EVAL * b->winner;

    //Fonction du compilateur GCC permettant de compter le nombre d'octets à 1
    return __builtin_popcount(b->whiteMask)-__builtin_popcount(b->blackMask);

}


int min_max_search(int alpha, int beta, const int depth, board * restrict b,
const uint16_t * restrict list_winning_masks, const int taille_liste)
{
    if(depth == 0)      //Si on atteint la profondeur, on évalue
        return eval(b);

    if(b->winner>-2)//Si la partie est terminée
        return eval(b);

    if(b->last_grid == -1)
        return eval(b);

    int best_eval = -MAX_EVAL*b->player;
    

    //On parcourt tous les coups possibles
    const int grille = b->last_grid;
    const uint16_t filled_squares = b->listeSubBoards[grille].blackMask|b->listeSubBoards[grille].whiteMask;


    if(!(filled_squares == 0ULL))//Evite de chercher dans des carrés vides et de ralentir le programme pour rien
    {

        for(int square = 0; square<9; square ++) if(!is_filled(filled_squares,square))//Si le carré n'est pas pris
        {
            play(b,9*grille+square,list_winning_masks,taille_liste,0); //On joue le coup
            const int eval_coup = min_max_search(alpha,beta,depth-1,b,list_winning_masks,taille_liste); //On évalue la nouvelle position 
            
            unplay(b,9*grille+square,grille); //On annule le coup
            
            

            if(b->player == 1)//Les blancs jouent
            {
                //eval = max(eval,eval_coup)
                if(eval_coup>best_eval)
                    best_eval = eval_coup;

                //Elagage alpha beta
                if(alpha<eval_coup)
                    alpha = eval_coup;

                if(beta<=alpha)
                    return best_eval;
            }else //Les noirs jouent
            {
                //eval = min(eval,eval_coup)
                if(eval_coup<best_eval)
                    best_eval = eval_coup;


                //Elagage alpha beta
                if(beta > eval_coup)
                    beta = eval_coup;

                if(beta <=alpha)
                    return best_eval;
            }
        }
    }
    return best_eval;
}




int computer_play(board * restrict b,const int max_depth, const uint16_t * restrict list_winning_masks, const int taille_liste)
{
    
    if(b->last_grid == -1)
    {
        const uint16_t finished_grids = b->blackMask|b->whiteMask|b->equalMask;
        for(int i = 0;i<9;i++) if(!is_filled(finished_grids,i))
        {
            return i*9+4; //Le coup du milieu d'une grille non prise
        }
    }

    int best_eval = -MAX_EVAL;
    int best_move = -1;
    const int player = b->player;

    const int grille = b->last_grid;
    uint16_t filled_squares = b->listeSubBoards[grille].blackMask|b->listeSubBoards[grille].whiteMask;

    for(int square = 0; square<9; square ++) if(!is_filled(filled_squares,square))//Si le carré n'est pas pris
    {
        play(b,9*grille+square,list_winning_masks,taille_liste,0); //On joue le coup
        const int eval_coup = min_max_search(-MAX_EVAL,MAX_EVAL,max_depth,b,list_winning_masks,taille_liste); //On évalue la nouvelle position 
        unplay(b,9*grille+square,grille); //On annule le coup
        if(eval_coup *player > best_eval)
        {
            best_eval = eval_coup * player;
            best_move = 9*grille + square;
        }
    }
    return best_move;
}
