#include "mask.h"

int is_filled(uint16_t mask, int i)
{
    if(mask & (1ULL << i))
        return 1;
    return 0;
}

void fill_square(uint16_t * mask, int i)
{
    *mask |=  1ULL<<i;
}

void read_winning_masks(uint16_t ** list, int * taille)
{
    FILE *fichier;
    // Ouvrir le fichier en mode binaire de lecture
    fichier = fopen(WINNING_MOVES_DEST, "rb");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    /// Se déplacer à la fin du fichier
    if (fseek(fichier, 0, SEEK_END) != 0) {
        perror("Erreur lors du déplacement à la fin du fichier");
        fclose(fichier);
        return;
    }

    // Obtenir la position actuelle, qui est la taille du fichier
    long taille_fichier = ftell(fichier);
    *taille = taille_fichier/sizeof(uint16_t);
    // Revenir au début du fichier
    rewind(fichier);
        

    // Allouer de la mémoire pour la liste
    *list = malloc(taille_fichier);
    
    if (*list == NULL) {
        perror("Erreur lors de l'allocation de mémoire");
        fclose(fichier);
        return;
    }
    size_t elt_lus = fread(*list, sizeof(uint16_t), taille_fichier, fichier);
    if(elt_lus * sizeof(uint16_t)!=(size_t)taille_fichier){
        perror("Erreur lors de la lecture du fichier");
        free(*list);
    }
    
    // Fermer le fichier
    fclose(fichier);
}


void generate_winning_masks()
{
    
    uint16_t mask;

    FILE * file = fopen(WINNING_MOVES_DEST,"wb");

    if(!file)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    //Les lignes
    for(int i=0; i<3;i++){
        mask = 0ULL;
        for(int j=0;j<3;j++){
            fill_square(&mask,i*3 + j);
        }
        size_t written_elt = fwrite(&mask,sizeof(mask),1,file);
        if(written_elt!=1)
        {
            perror("Erreur lors de l'écriture dans le fichier");
            fclose(file);
            return;
        }
    }

    //Les colonnes
    for(int i=0; i<3;i++){
        mask = 0ULL;
        for(int j=0;j<3;j++){
            fill_square(&mask,i + j*3);
        }
        size_t written_elt = fwrite(&mask,sizeof(mask),1,file);
        if(written_elt!=1)
        {
            perror("Erreur lors de l'écriture dans le fichier");
            fclose(file);
            return;
        }
    }

    //Les diagonales
    mask = 0ULL;
    for(int i=0; i<3;i++){
        fill_square(&mask,i+i*3);
    }
    size_t written_elt = fwrite(&mask,sizeof(mask),1,file);
    if(written_elt!=1)
    {
        perror("Erreur lors de l'écriture dans le fichier");
        fclose(file);
        return;
    }
    mask = 0ULL;
    for(int i=0; i<3;i++){
        
        fill_square(&mask,2-i+i*3);  
    }
    written_elt = fwrite(&mask,sizeof(mask),1,file);
    if(written_elt!=1)
    {
        perror("Erreur lors de l'écriture dans le fichier");
        fclose(file);
        return;
    }
    fclose(file);
}


void show_mask(const uint16_t mask)
{
    for(int i=0;i<9;i++)
    {
        if(i%3==0)
            printf("\n");
        if(is_filled(mask,i))
        {
            printf("#");
        }else{
            printf(".");
        }
    }
    printf("\n");
}