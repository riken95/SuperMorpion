#include "move.h"

moveStack * addMove(moveStack * restrict stack, const move i)
{
    moveStack * newMove = malloc(sizeof(moveStack));
    newMove->i = i;
    newMove->prevMove = stack;
    

    return newMove;
}


move removeMove(moveStack ** restrict stack)
{
    //Cas où la pile est vide
    if(!stack)
        return 0;

    moveStack * tempStack = *stack;

    move i = tempStack->i;
    *stack = tempStack->prevMove;
    free(tempStack);
    return i;
}
