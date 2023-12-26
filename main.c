#include "superMorpion/board.h"


int main()
{
    generate_winning_masks();
    uint16_t * liste_masques;
    board * b = init_board();
    read_winning_masks(&liste_masques);
    show_board(b);
    return 0;
}