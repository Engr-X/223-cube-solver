#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "dfs_solver.h"

/**
 *                    Pushes a new node to the head of a move stack.
 *
 * This function pushes a new node to the head of a move stack and sets the head and tail of the stack to that node.
 *
 * @param stack             The move stack to push the new node to.
 * @param move              The move to push to the stack.
 */
void move_list_push_head(MoveList* stack, Move move)
{
    MoveNode* node = (MoveNode*)(malloc(sizeof(MoveNode)));
    node -> move = move;
    node -> next = NULL;
    node -> prev = NULL;

    stack -> head = node;
    stack -> last = node;
    stack -> size = 1;
}

/**
 *                    Pushes a new node to the tail of a move stack.
 *
 * This function pushes a new node to the tail of a move stack and sets the tail of the stack to that node.
 *
 * @param stack             The move stack to push the new node to.
 * @param move              The move to push to the stack.
 */
void move_list_push(MoveList* stack, Move move)
{
    MoveNode* node = (MoveNode*)(malloc(sizeof(MoveNode)));
    node -> move = move;
    node -> next = NULL;
    node -> prev = stack -> last;

    stack -> last -> next = node;
    stack -> last = node;
    stack -> size++;
}

/**
 *                       Pops the last node from a move stack.
 *
 * This function pops the last node from a move stack, and decrements the size of the stack.
 *
 * @param stack             The move stack to pop the node from.
 */
void move_list_pop(MoveList* stack)
{
    MoveNode* node = stack -> last;

    if (stack -> size == 1)
    {
        stack -> head = NULL;
        stack -> last = NULL;
    }
    else
        stack -> last = stack -> last -> prev;

    stack -> size--;

    free(node);
}

/**
 *                    Frees all the memory allocated by a move stack.
 *
 * This function traverses the move stack, freeing each node in the stack. It is
 * recommended to call this function after the move stack is no longer needed to
 * prevent memory leaks.
 *
 * @param stack             The move stack to free.
 */
void move_list_free(MoveList* stack)
{
    MoveNode* node = stack -> head;

    while (node != NULL)
    {
        MoveNode* next = node -> next;
        free(node);
        node = next;
    }
}

/**
 *                       Prints all the steps in a move stack to the console.
 *
 * This function is for debugging purpose.
 *
 * @param stack                 The move stack to print.
 */
void move_list_print(MoveList* stack)
{
    char res[1024] = "steps: \0";

    MoveNode* node = stack -> head;

    while (node != NULL)
    {
        strcat(res, node -> move.symbol);
        strcat(res, "\t\0");
        node = node -> next;
    }

    puts(res);
}

/**
 *                       Checks edge phases is correct.
 *
 * This function takes an initial edge phase and a sequence of moves,
 * and checks if the final edge phase of the sequence of moves is one of the edge phases.
 * If the final edge phase of the sequence of moves is one of the edge phases,
 * the function returns true; otherwise, it returns false.
 *
 * @param phase                 The initial edge phase.
 * @param path                  A sequence of moves to check.
 *
 * @return                      True if the final edge phase is one of the edge phases, false otherwise.
 */

bool dfs_check_edge_phase(uint8_t phase, MoveList* path)
{
    MoveNode* node = path -> head;

    while (node != NULL)
    {
        uint8_t a = node -> move.serial;

        switch (a)
        {
            case 0: {phase = edge_R_transform(phase); break;}
            case 1: {phase = edge_L_transform(phase); break;}
            case 2: {phase = edge_F_transform(phase); break;}
            case 3: {phase = edge_B_transform(phase); break;}
            case 4:
            case 5:
            case 6: break;
            case 7: {phase = edge_E_transform(phase); break;}
            case 8: {phase = edge_EPrime_transform(phase); break;}
            case 9: {phase = edge_E2_transform(phase); break;}
            case 10:
            case 11:
            case 12: break;
            case 13: {phase = edge_E_transform(phase); break;}
            case 14: {phase = edge_EPrime_transform(phase); break;}
            case 15: {phase = edge_E2_transform(phase); break;}
            case 16: {phase = edge_EPrime_transform(phase); break;}
            case 17: {phase = edge_E_transform(phase); break;}
            case 18: {phase = edge_E2_transform(phase); break;}
            default: break;
        }

        node = node -> next;
    }

    return phase == 3 ||
            phase == edge_E_transform(3) ||
            phase == edge_EPrime_transform(3) ||
            phase == edge_E2_transform(3);
}

/**
 *                       A helper function to perform DFS algorithm.
 *
 * This function takes the current state of the cube, the current edge phase, a boolean indicating whether
 * all edge phases are zero, the current path of moves, the last move in the path, a 2D array of moves, an
 * array of original states, the minimum depth, the maximum depth, and a pointer to the solution count.
 *
 * If the current state is the original state, the function checks if the edge phase is correct and if so,
 * prints out the path and increments the solution count. If the current depth is greater than or equal to
 * the maximum depth, the function returns.
 *
 * Otherwise, the function iterates through all possible moves from the last move, pushes the current move onto
 * the path, and calls itself recursively. After the recursive call, the function pops the current move from
 * the path.
 *
 * @param state                 The current state of the cube.
 * @param edges_phase_state     The current edge phase.
 * @param edges_all0            A boolean indicating whether all edge phases are zero.
 * @param path                  The current path of moves.
 * @param last_move             The last move in the path.
 * @param moves_map             A 2D array of moves.
 * @param original_states       An array of original states.
 * @param min_depth             The minimum depth of the solution.
 * @param max_depth             The maximum depth of the solution.
 * @param solution_count        A pointer to the solution count.
 */
void dfs_iterator(uint64_t state, uint8_t edges_phase_state, bool edges_all0,
                  MoveList* path, int16_t last_move, const Move* moves_map, const int* original_states,
                  uint8_t min_depth, uint8_t max_depth, uint16_t* solution_count)
{
    if (path -> size >= min_depth && is_original_state(state, original_states))
    {
        if (edges_all0 || dfs_check_edge_phase(edges_phase_state, path))
        {
            (*solution_count)++;
            move_list_print(path);
        }
    
        return;
    }

    if (path -> size >= max_depth)
        return;

    int8_t index = 1;

    while (true)
    {
        const Move current_move = moves_map[last_move * 19 + index];

        if (current_move.transform == NULL)
            break;

        move_list_push(path, current_move);
        dfs_iterator(current_move.transform(state), edges_phase_state, edges_all0,
                    path, current_move.serial, moves_map, original_states, min_depth, max_depth, solution_count);
        move_list_pop(path);

        index++;
    }
}

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
                     uint32_t state, uint8_t edges_phase_state, uint8_t min_depth, uint8_t max_depth)
{
    const uint8_t moves_size = 19;
    const Move ALL_MOVES[19] = {R, L, F, B, U, UPrime, U2, E, EPrime, E2, D, DPrime, D2, Uw, UwPrime, Uw2, Dw, DwPrime, Dw2};
    const bool edges_all0 = (state & 0xffu) == 0;

    uint16_t solution_count = 0;
    uint64_t current_time = get_current_time();

    puts("start searching");
    
    for (uint8_t i = 0; i < moves_size; i++)
    {
        const Move second_move = moves_map[i * moves_size + 1];

        if (second_move.transform != NULL)
        {
            MoveList path;
            const Move first_move = ALL_MOVES[i];
            move_list_push_head(&path, first_move);
            dfs_iterator(first_move.transform(state), edges_phase_state, edges_all0,
                         &path, first_move.serial, moves_map, original_states, min_depth, max_depth, &solution_count);
            
            
            free(path.head);
        }
    }

    printf("search end in %lf (s), find total %d solutions: ", (get_current_time() - current_time) / 1000.0, solution_count);
}