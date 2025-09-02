#ifndef CUBE_SOLVER_H
#define CUBE_SOLVER_H

#include <stdint.h>

#include <cJSON.h>

#include "move.h"

typedef struct solver_param
{
    const Move* moves;
    const Move* moves_map;
    const int* original_states;
    uint32_t state;
    uint8_t edges_phase_state;
    uint8_t min_depth;
    uint8_t max_depth;
} SolverParam;

void get_solver_param(const cJSON* json, SolverParam* solver_param);

/**
 *                       Solves a cube given its settings and configuration.
 *
 * This function takes a JSON object containing the settings and configuration of the cube
 * and solves it using the specified algorithm. The JSON object must contain the following
 * items: "max_depth", "min_depth", "corners", "edges", "moves" and "moves_map". The "corners"
 * and "edges" items must contain arrays of 8 and 4 bytes respectively, representing the
 * corners and edges of the cube. The "moves" and "moves_map" items must contain arrays of
 * strings, representing the moves and the moves map of the cube.
 *
 * @param json                  The JSON object containing the settings and configuration of the
 *                               cube.
 */
void cube_solver(const cJSON* json);

#endif