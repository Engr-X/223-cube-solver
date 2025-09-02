#ifndef CUBE_API_H
#define CUBE_API_H

#include "move.h"

typedef struct move_node
{
    Move move;
    struct move_node* next;
    struct move_node* prev;
} MoveNode;

typedef struct move_list
{
    int16_t size;
    MoveNode* head;
    MoveNode* last;
} MoveList;

#endif