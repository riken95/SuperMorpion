#include "superMorpion/board.h"


int main()
{
    generate_winning_masks();
    uint16_t * liste_masques;
    read_winning_masks(&liste_masques);
    return 0;
}