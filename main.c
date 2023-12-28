#include "superMorpion/program.h"
#include <ctype.h> //tolower()
#include <string.h> //strcmp()
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
    int fin_prog = 0;
    while(!fin_prog)
    {
        if(fgets(buffer,sizeof(buffer),stdin))//Lecture de l'entrée utilisateur
        {
            int grid;
            char column;
            int line;
            int depth;
            if(sscanf(buffer,"%d %c%d",&grid,&column,&line)==3) //On vérifie que le format correspond
            {
                column = tolower(column);
                int column_n = column-'a';
                if((unsigned int)column_n >8 || (unsigned int)grid >8 || (unsigned int) line > 8)
                {
                    printf("Format invalide\n");
                }else{
                    play(b,9*grid+3*line+column_n,liste_masques,taille,1);
                    show_board(b);
                }
                
            }
            else if(!strcmp(buffer,"quit\n"))//Arret programme
            {
                ++fin_prog;
            }
            else if(sscanf(buffer,"play %d",&depth)==1)//Ordonne au programme de jouer
            {
                play(b,computer_play(b,depth,liste_masques,taille),liste_masques,taille,0);
                show_board(b);

            }
            else{
                printf("Format invalide !\n");
            }
        }
    }
    free(liste_masques);
    free_board(b);
    return 0;
}