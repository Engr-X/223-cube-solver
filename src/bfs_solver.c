#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bfs_solver.h"

/**
 * Allocate a new Node and optionally link it to a parent.
 *
 * @param parrent               Node to link to, or NULL if this Node is to be the head of a list.
 * @param state                 The state of the node.
 * @param steps                 The number of steps of the node.
 * @param steps_size            The number of steps size of the node.
 *
 * @return                      The newly allocated Node.
 */
Node* node_create(Node* parrent, uint32_t state, uint64_t steps, uint8_t steps_size)
{
    Node* node = (Node*)(malloc(sizeof(Node)));

    node -> next = NULL;
    node -> state = state;
    node -> steps = steps;
    node -> steps_size = steps_size;

    if (parrent != NULL)
        parrent -> next = node;

    return node;
}

/**
 *                       Prints the contents of a queue as a linked list.
 *
 * This is a debugging function that prints the contents of a queue as a linked list.
 * Each node is printed as a pointer address, and the list is terminated with a newline.
 *
 * @param queue                 The queue to print.
 */
void queue_print(Queue* queue)
{
    Node* node = queue -> head;

    while (node != NULL)
    {
        printf("%p -> ", node);
        node = node -> next;
    }

    puts("\0");
}

/**
 *                       Adds a new node to the head of the queue (only can use when queue is empty !!!).
 *
 * This function creates a new node with the given state, steps, and steps_size,
 * and sets it as the head of the queue. The new node also becomes the last node
 * in the queue, and the queue size is set to 1.
 *
 * @param queue                 The queue to which the new node is added.
 * @param state                 The state of the new node.
 * @param steps                 The number of steps of the new node.
 * @param steps_size            The number of steps size of the new node.
 */
void queue_push_head(Queue* queue, uint32_t state, uint64_t steps, uint8_t steps_size)
{
    queue -> head = node_create(NULL, state, steps, steps_size);
    queue -> last = queue -> head;
    queue -> size = 1;
}

/**
 *                       Adds a new node to the end of the queue.
 *
 * This function creates a new node with the given state, steps, and steps_size,
 * and appends it to the end of the queue. The queue size is incremented by 1.
 *
 * @param queue                 The queue to which the new node is added.
 * @param state                 The state of the new node.
 * @param steps                 The number of steps of the new node.
 * @param steps_size            The number of steps size of the new node.
 */
void queue_push(Queue* queue, uint32_t state, uint64_t steps, uint8_t steps_size)
{
    queue -> last = node_create(queue -> last, state, steps, steps_size);

    queue -> size++;
}

/**
 *                       Removes and returns the node at the head of the queue.
 *
 * This function decreases the queue size by one, updates the head to the next node,
 * and returns the original head node. It assumes that the queue is not empty when called.
 *
 * @param queue                 The queue from which to pop the head node.
 *
 * @return                      The node removed from the head of the queue.
 */

Node* queue_pop(Queue* queue)
{
    queue -> size--;
    Node* result = queue -> head;
    queue -> head = queue -> head -> next;

    return result;
}

/**
 *                       Initializes and returns an empty queue.
 *
 * This function creates a new Queue instance with size set to 0, and both
 * head and last pointers initialized to NULL, indicating that the queue
 * is empty.
 *
 * @return                      A newly created empty queue.
 */
Queue queue_create()
{
    Queue queue;
    queue.size = 0;
    queue.head = NULL;
    queue.last = NULL;

    return queue;
}

/**
 *                       Prints the steps required to solve a cube.
 *
 * This function takes a sequence of moves represented as a bit packed
 * integer, and prints out the corresponding move sequence as a string.
 *
 * @param map                   An array of moves to use for looking up move names.
 * @param steps                 The sequence of moves to print, bit packed into a uint64_t.
 * @param size                  The number of moves in the sequence.
 * @param moves_bits            The number of bits required to represent a move, (if there are 3 moves available, moves_bits = 2; if there are 8 moves available, moves_bits = 3).
 * @param moves_musk            A mask value to use when unpacking the moves from the steps, (if moves_bits = 3 => moves_musk = 111b).
 */
void bfs_print_step(const Move* map, uint64_t steps, uint8_t size, uint8_t moves_bits, uint8_t moves_musk)
{
    char string[128] = "steps: \0";

    for (uint8_t i = 0; i < size; i++)
    {
        uint8_t a = steps >> (moves_bits * (size - 1 - i)) & moves_musk; // unpack single move
        strcat(string, map[a].symbol);
        strcat(string, "\t");
    }
    
    puts(string);
}

/**
 *                       Checks edge phases is correct.
 *
 * This function takes an initial edge phase, a sequence of moves, and the size
 * of the sequence, and checks if the final edge phase of the sequence of moves
 * is one of the edge phases. If the final edge phase of the sequence of moves is
 * one of the edge phases, the function returns true; otherwise, it returns false.
 *
 * @param phase                 The initial edge phase.
 * @param steps                 A sequence of moves to check.
 * @param steps_size            The size of the sequence of moves.
 * @param moves_bits            The number of bits needed to represent a single move.
 * @param moves_musk            A mask of all possible moves.
 *
 * @return                      True if the final edge phase is one of the edge phases, false otherwise.
 */
bool bfs_check_edge_phase(uint8_t phase, uint64_t steps, uint8_t steps_size, uint8_t moves_bits, uint8_t moves_musk)
{
    for (uint8_t i = 0; i < steps_size; i++)
    {
        uint8_t a = steps >> (moves_bits * (steps_size - 1 - i)) & moves_musk;

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
    }

    return phase == 3 ||
            phase == edge_E_transform(3) ||
            phase == edge_EPrime_transform(3) ||
            phase == edge_E2_transform(3);
}

/**
 *                       Solves a cube using BFS algorithm.
 *
 * This function takes an array of moves, a 2D array of moves, an array of original states,
 * the initial state, the initial edge phase, the minimum depth, and the maximum depth,
 * and solves a cube using BFS algorithm. If the cube is solvable, the function prints out the solution and returns true;
 * otherwise, the function returns false.
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
                uint32_t state, uint8_t edges_phase_state, uint8_t min_depth, uint8_t max_depth)
{
    // there are 19 possible moves in 223 cube
    const uint8_t moves_size = 19;
    const Move ALL_MOVES[19] = {R, L, F, B, U, UPrime, U2, E, EPrime, E2, D, DPrime, D2, Uw, UwPrime, Uw2, Dw, DwPrime, Dw2}; //all possible moves
    Move moves_map_2d[19][19] = {};

    uint8_t first_valid_index = 0;

    // convert moves_map to 2d array
    for (uint8_t i = 0; i < moves_size; i++)
    {
        if (moves[i].transform != NULL && moves[i].serial > first_valid_index)
            first_valid_index = moves[i].serial;

        for (uint8_t j = 0; j < moves_size; j++)
            moves_map_2d[i][j] = moves_map[i * moves_size + j];
    }

    // represent edges is zero or not. if is zero then we not consider the edge in solution. if is not zero then we consider the edge
    const bool edges_all0 = (state & 0xff) == 0;
    const uint8_t moves_bits = first_valid_index == 0 ? 1 : log2(first_valid_index) + 1; // how many bits are needed to represent all moves
    const uint8_t moves_mask = (1 << moves_bits) - 1; // musk of moves bits

    uint8_t level = 0; //current step
    uint16_t solution_count = 0;
    uint64_t current_time = get_current_time(); // start time
    Queue queue = queue_create();

    // 
    for (uint8_t i = 0; i < moves_size; i++)
    {
        const Move second_move = moves_map_2d[i][1];

        if (second_move.transform != NULL)
        {
            Move m = moves[i];
            if (i == 0) queue_push_head(&queue, m.transform(state), m.serial, 1);
            else queue_push(&queue, m.transform(state), m.serial, 1);
        }
    }


    while (queue.size > 0)
    {
        Node* node = queue_pop(&queue);

        const uint32_t current_state = node -> state;
        const uint64_t current_steps = node -> steps;
        const uint8_t current_steps_size = node -> steps_size;
        const uint8_t last_step = current_steps & moves_mask;

        if (is_original_state(current_state, original_states))
        {
            if (edges_all0 || bfs_check_edge_phase(edges_phase_state, current_steps, current_steps_size, moves_bits, moves_mask))
            {
                solution_count++;
                bfs_print_step(ALL_MOVES, current_steps, current_steps_size, moves_bits, moves_mask);
            }
    
            free(node);
            continue;
        }

        if (current_steps_size > level)
        {
            level++;
            printf("searching level: %d, current deque size: %lld\n", current_steps_size, queue.size);
        }

        if (current_steps_size < max_depth)
        {
            const uint8_t new_steps_size = current_steps_size + 1;
            uint8_t index = 1;

            while (true)
            {
                Move m = moves_map_2d[last_step][index++];

                if (m.transform == NULL || m.serial == -1)
                    break;

                const uint32_t new_state = m.transform(current_state);
                const uint64_t new_steps = current_steps << moves_bits | m.serial;

                queue_push(&queue, new_state, new_steps, new_steps_size);
            }
        }

        free(node);    
    }

    printf("search end in %lf (s), find total %d solutions: ", (get_current_time() - current_time) / 1000.0, solution_count);
}