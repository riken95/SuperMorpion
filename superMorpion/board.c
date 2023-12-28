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
    board * b = (board *) malloc(sizeof(board));

    //Initialisation des sous-masques à 0
    for(int i=0;i<9;i++){
        b->listeSubBoards[i].blackMask = 0ULL;
        b->listeSubBoards[i].whiteMask = 0ULL;
    }
       


    //Initialisation des masques à 0
    b->blackMask = 0ULL;
    b->equalMask = 0ULL;
    b->whiteMask = 0ULL;

    b->player = 1; //Les blancs commencent
    b->winner = -2;
    return b;
}


void free_subBoard(subBoard * restrict p)
{
    free(p);
}

void free_board(board * restrict p)
{
    free(p);
}


void show_board(const board * restrict p)
{
    uint16_t masque_occupe = p->blackMask|p->equalMask|p->whiteMask;
    for(int j =0;j<9;j++)
    for(int i =0;i<9;i++)
    {
        int grille = i/3 + 3*(j/3);
        if(i%3 == 0 && i>0)
            printf("|");
        if(j%3 == 0 && j > 0 && i==0)
            printf("___________\n");
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
            if(is_filled(p->listeSubBoards[grille].blackMask,i%3+3*(j%3)))
                printf("X");
            else if(is_filled(p->listeSubBoards[grille].whiteMask,i%3+3*(j%3)))
                printf("O");
            else
                printf(" ");
        }
        if(i==8)
            printf("\n");
    }
}

/**
 * @brief  Détermine si la sous-grille spécifiée est complétée
 * @note   
 * @param  b: le plateau
 * @param  grid_n: le numéro de la sous-grille
 * @param  player: Si égal à 0 on vérifie pour les deux joueurs, sinon pour l'un des 2
 * @param  list_winning_masks: La liste des masques binaires des positions gagnantes
 * @param  taille_liste: La taille de la liste précédente
 * @retval 0 : égalité | -2 : la grille n'est pas pleine | 1 : les blancs gagnent | -1 : les noirs gagnent
 *
*/
int grid_is_filled(const board * restrict b, const int grid_n, const int player, const uint16_t * restrict list_winning_masks, const int taille_liste)
{
    if(player == 0)//mode où on check si la grille est pleine sans avoir aucune info sur le joueur qui a joué en dernier
    {
        
        if(is_filled(b->blackMask,grid_n))
            return -1;
        if(is_filled(b->whiteMask,grid_n))
            return 1;
        if(is_filled(b->equalMask,grid_n))
            return 0;

        for(int i= 0;i<taille_liste;i++)
        {
            if(list_winning_masks[i]==((list_winning_masks[i])&(b->listeSubBoards[grid_n].blackMask)))
            {
                return -1;
            }
            if(list_winning_masks[i]==((list_winning_masks[i])&(b->listeSubBoards[grid_n].whiteMask)))
            {
                return 1;
            }
        }
    }
    else if(player==1)//Ici on part du principe que le joueur blanc vient de jouer et que la grille n'était pas pleine avant
    {
        for(int i= 0;i<taille_liste;i++)
        {
            if(list_winning_masks[i]==((list_winning_masks[i])&(b->listeSubBoards[grid_n].whiteMask)))
            {
                return 1;
            }
        }
    }
    else if(player==-1)//Ici on part du principe que le joueur noir vient de jouer et que la grille n'était pas pleine avant
    {
        for(int i= 0;i<taille_liste;i++)
        {
            if(list_winning_masks[i]==((list_winning_masks[i])&(b->listeSubBoards[grid_n].blackMask)))
            {
                return -1;
            }
        }
    }
    if(((b->listeSubBoards[grid_n].blackMask|b->listeSubBoards[grid_n].whiteMask)&0x1FF)==0x1FF) //0x1FF : 9 premiers bits égaux à 1
    {
        return 0; //La grille est pleine
    }
    return -2;
}


int game_is_over(const board * restrict b, const uint16_t * restrict list_winning_masks, const int taille_liste)
{
    for(int i= 0;i<taille_liste;i++)
    {
        if(list_winning_masks[i]==((list_winning_masks[i])&(b->whiteMask))) //Les blancs gagnent
            return 1;
        if(list_winning_masks[i]==((list_winning_masks[i])&(b->blackMask)))  //Les noirs gagnent
            return -1;
        
        if(((b->whiteMask|b->blackMask|b->equalMask)&0x1FF)==0x1FF) //0x1FF : 9 premiers bits égaux à 1
            return 0; //Egalité 
    }
    return -2; //La partie n'est pas terminée


}

int play(board * restrict b,const int m, const uint16_t * restrict list_winning_masks, const int taille_liste)
{
    if((unsigned int)m>=81)
    {
        printf("Veuillez saisir un coup correct !\n");
        return -1;
    }
    uint16_t finished_grids = b->blackMask|b->equalMask|b->whiteMask;
    if(is_filled(finished_grids,m/9))
    {
        printf("Cette grille est déjà terminée !\n");
        return -2;
    }
    uint16_t occupied_squares = b->listeSubBoards[m/9].blackMask|b->listeSubBoards[m/9].whiteMask;
    if(is_filled(occupied_squares,m%9))
    {
        printf("Cette case est déjà occupée !\n");
        return -3;
    }

    if(b->player==1)//Les blancs jouent
    {
        fill_square(&(b->listeSubBoards[m/9].whiteMask),m%9);
    }
        
    else//Les noirs jouent
    {
        fill_square(&(b->listeSubBoards[m/9].blackMask),m%9);
    }
    int grid_is_filled_n = grid_is_filled(b,m/9,b->player,list_winning_masks,taille_liste);
    switch (grid_is_filled_n)
    {
    case 1:
        fill_square(&b->whiteMask,m/9);
        break;
    case -1:
        fill_square(&b->blackMask,m/9);
        break;
    case 0:
        fill_square(&b->equalMask,m/9);
    default:
        break;
    }


    if(grid_is_filled_n>-2) //S'il y a un gagnant on le spécifie
        b->winner = game_is_over(b,list_winning_masks,taille_liste);
        
    
    b->player*=-1;//On change de joueur
    return 0;
}




void unplay(board * restrict b,const int m)
{
    int grille = m/9;
    empty_square(&b->blackMask,grille);
    empty_square(&b->whiteMask,grille);
    empty_square(&b->equalMask,grille);
    empty_square(&b->listeSubBoards[grille].blackMask,m%9);
    empty_square(&b->listeSubBoards[grille].whiteMask,m%9);
    b->player *= -1;
    b->winner = -2;
}
