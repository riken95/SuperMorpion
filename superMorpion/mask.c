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

void read_winning_masks(uint16_t ** list)
{
    FILE *fichier;
    long taille_fichier;

    // Ouvrir le fichier en mode binaire de lecture
    fichier = fopen(WINNING_MOVES_DEST, "rb");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Déterminer la taille du fichier
    fseek(fichier, 0, SEEK_END); // Déplacer le curseur à la fin du fichier
    taille_fichier = ftell(fichier); // Récupérer la position du curseur (la taille du fichier)
    fseek(fichier, 0, SEEK_SET); // Réinitialiser le curseur au début du fichier

    // Allouer de la mémoire pour la liste
    *list = malloc(taille_fichier);
    
    if (*list == NULL) {
        perror("Erreur lors de l'allocation de mémoire");
        fclose(fichier);
        return;
    }
    int i = 0;
    while (fread(&(*list)[i++], sizeof(uint16_t), 1, fichier) == 1) {
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
        size_t written_elt = fwrite(&mask,1,sizeof(mask),file);
        if(written_elt!=sizeof(mask))
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
        size_t written_elt = fwrite(&mask,1,sizeof(mask),file);
        if(written_elt!=sizeof(mask))
        {
            perror("Erreur lors de l'écriture dans le fichier");
            fclose(file);
            return;
        }
    }

    //Les diagonales
    for(int i=0; i<3;i++){
        mask = 0ULL;
        fill_square(&mask,i+i*3);
        size_t written_elt = fwrite(&mask,1,sizeof(mask),file);
        if(written_elt!=sizeof(mask))
        {
            perror("Erreur lors de l'écriture dans le fichier");
            fclose(file);
            return;
        }
    }
    for(int i=0; i<3;i++){
        mask = 0ULL;
        fill_square(&mask,3-i+i*3);
        size_t written_elt = fwrite(&mask,1,sizeof(mask),file);
        if(written_elt!=sizeof(mask))
        {
            perror("Erreur lors de l'écriture dans le fichier");
            fclose(file);
            return;
        }
    }
}
