#include "superMorpion/board.h"
#include <ctype.h> //tolower()
#define MAX_BUFFER_STD 128

int main()
{
    generate_winning_masks();
    uint16_t * liste_masques;
    int taille;
    board * b = init_board();
    read_winning_masks(&liste_masques,&taille);
    show_board(b);

    char buffer[MAX_BUFFER_STD];
    while(1)
    {
        if(fgets(buffer,sizeof(buffer),stdin))//Lecture de l'entrée utilisateur
        {
            int grid;
            char column;
            int line;
            if(sscanf(buffer,"%d %c%d",&grid,&column,&line)==3) //On vérifie que le format correspond
            {
                column = tolower(column);
                int column_n = column-'a';
                play(b,9*grid+3*line+column_n,liste_masques,taille);
                show_board(b);
            }else{
                printf("Format invalide !\n");
            }
        }
    }
    return 0;
}