#ifndef DFS_SOLVER_H
#define DFS_SOLVER_H

#include <stdint.h>

#include "API.h"
#include "utils.h"
#include "move.h"

/**
 *                       Solves a cube using DFS algorithm.
 *
 * This function takes an array of moves, a 2D array of moves, an array of original states,
 * the initial state, the initial edge phase, the minimum depth, and the maximum depth,
 * and solves a cube using DFS algorithm. If the cube is solvable, print all solutions by
 * using DFS algorithm. If the cube is not solvable, print nothing.
 *
 * @param moves                 An array of moves to use for solving the cube.
 * @param moves_map             A 2D array of moves to use for solving the cube.
 * @param original_states       An array of original states to check against.
 * @param state                 The initial state of the cube.
 * @param edges_phase_state     The initial edge phase of the cube.
 * @param min_depth             The minimum depth of the solution.
 * @param max_depth             The maximum depth of the solution.
 */
void cube_dfs_solver(const Move* moves, const Move* moves_map, const int* original_states,
                     uint32_t state, uint8_t edges_phase_state, uint8_t min_depth, uint8_t max_depth);
#endif