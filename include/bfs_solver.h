#ifndef BFS_SOLVER_H
#define BFS_SOLVER_H

#include <stdint.h>
#include "move.h"

typedef struct node
{
    uint64_t steps; // records steps better than the linkedlist
    struct node* next;
    uint32_t state; // current steps
    int8_t steps_size; // how many steps

} Node;

typedef struct queue
{
    int64_t size;
    Node* head;
    Node* last;
} Queue;

/**
 *                       Solves a cube using BFS algorithm.
 *
 * This function takes an array of moves, a 2D array of moves, an array of original states, the initial state,
 * the initial edge phase, the minimum depth, and the maximum depth, and solves a cube using BFS algorithm.
 * If the cube is solvable, print all solutions by using BFS algorithm.
 *
 * @param moves                 An array of moves to use for solving the cube.
 * @param moves_map             A 2D array of moves to use for solving the cube.
 * @param original_states       An array of original states to check against.
 * @param state                 The initial state of the cube.
 * @param edges_phase_state     The initial edge phase of the cube.
 * @param min_depth             The minimum depth of the solution.
 * @param max_depth             The maximum depth of the solution.
 */
void cube_bfs_solver(const Move* moves, const Move* moves_map, const int* original_states,
                     uint32_t state, uint8_t edges_phase_state, uint8_t min_depth, uint8_t max_depth);
#endif