#include "move.h"

moveStack * addMove_top(moveStack * restrict stack, const move i)
{
    moveStack * newMove = malloc(sizeof(moveStack));
    newMove->i = i;
    newMove->prevMove = stack;
    

    return newMove;
}
moveStack * addMove_bottom(moveStack * restrict stack, const move i)
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


moveStack * removeMove_ptr(moveStack ** restrict stack)
{
    //Cas où la pile est vide
    if(!stack)
        return NULL;

    moveStack * tempStack = *stack;
    if(!*stack)
    {
        return NULL;
    }
    *stack = tempStack->prevMove;
    return tempStack;
}


moveStack * addMove_top_ptr(moveStack * restrict stack, moveStack * restrict m)
{
    if(!m)
    {
        return stack;
    }
    m->prevMove = stack;
    return m;
}
