#ifndef CUBE_MOVE_H
#define CUBE_MOVE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct move
{
    uint8_t serial;
    char symbol[4];
    uint32_t (*transform)(uint32_t);
} Move;

/**
 * R_transform: corner and edge phase check for R move
 * corners: 0123 4567 => 0176 4532, edges: 0123 => 0132
 *
 * This function transforms the corner and edge phases for the R move. It takes
 * the 32-bit representation of the corner and edge phases as input and returns
 * the transformed corner and edge phases as a uint32_t.
 *
 * @state:                      32-bit representation of corner and edge phases
 * @return:                     transformed corner and edge phases
 *
 */
uint32_t R_transform(uint32_t state);

/**
 * L_transform: corner and edge phase check for L move
 * corners: 0123 4567 => 5423 1067, edges: 0123 => 1023
 *
 * This function transforms the corner and edge phases for the L move. It takes
 * the 32-bit representation of the corner and edge phases as input and returns
 * the transformed corner and edge phases as a uint32_t.
 *
 * @state:                      32-bit representation of corner and edge phases
 * @return:                     transformed corner and edge phases
 *
 */
uint32_t L_transform(uint32_t state);

/**
 * F_transform: corner and edge phase check for F move
 * corners: 0123 4567 => 7124 3560, edges: 0123 => 3120
 *
 * This function transforms the corner and edge phases for the F move. It takes
 * the 32-bit representation of the corner and edge phases as input and returns
 * the transformed corner and edge phases as a uint32_t.
 *
 * @state:                      32-bit representation of corner and edge phases
 * @return:                     transformed corner and edge phases
 *
 */
uint32_t F_transform(uint32_t state);

/**
 * B_transform: corner and edge phase check for B move
 * corners: 0123 4567 => 0653 4217, edges: 0123 => 0213
 *
 * This function transforms the corner and edge phases for the B move. It takes
 * the 32-bit representation of the corner and edge phases as input and returns
 * the transformed corner and edge phases as a uint32_t.
 *
 * @state:                      32-bit representation of corner and edge phases
 * @return:                     transformed corner and edge phases
 *
 */
uint32_t B_transform(uint32_t state);

/**
 * U_transform: corner phase check for U move
 * corners: 0123 4567 => 0653 4217, edges: 0123 => 0213
 *
 * This function transforms the corner phase for the U move. It takes the
 * 32-bit representation of the corner phase as input and returns the
 * transformed corner phase as a uint32_t.
 *
 * @state:                      32-bit representation of corner phase
 * @return:                     transformed corner phase
 *
 */
uint32_t U_transform(uint32_t state);

/**
 * UPrime_transform: corner phase check for U' move
 * corners (upper only): 0123 => 1230
 * 
 * @state:                      32-bit representation of corner phase
 * @return:                     transformed corner phase
 *
 * This function transforms the corner phase for the U' move. It takes the
 * 32-bit representation of the corner phase as input and returns the
 * transformed corner phase as a uint32_t.
 */
uint32_t UPrime_transform(uint32_t state);

/**
 * U2_transform: corner phase check for U2 move
 * corners (upper only): 0123 => 2301
 *
 * This function transforms the corner phase for the U2 move. It takes the
 * 32-bit representation of the corner phase as input and returns the
 * transformed corner phase as a uint32_t.
 *
 * @state:                      32-bit representation of corner phase
 * @return:                     transformed corner phase
 */
uint32_t U2_transform(uint32_t state);

/**
 * E_transform: edge phase check for E move
 * edges: 0123 => 3012
 *
 * This function transforms the edge phase for the E move. It takes the
 * 32-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint32_t.
 *
 * @state:                      32-bit representation of edge phase
 * @return:                     transformed edge phase
 */
uint32_t E_transform(uint32_t state);

/**
 * EPrime_transform: edge phase check for E' move
 * edges: 0123 => 1230
 *
 * This function transforms the edge phase for the E' move. It takes the
 * 32-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint32_t.
 *
 * @state:                      32-bit representation of edge phase
 * @return:                     transformed edge phase
 */
uint32_t EPrime_transform(uint32_t state);

/**
 * E2_transform: edge phase check for E2 move
 * edges: 0123 => 2301
 *
 * This function transforms the edge phase for the E2 move. It takes the
 * 32-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint32_t.
 *
 * @state:                      32-bit representation of edge phase
 * @return:                     transformed edge phase
 */
uint32_t E2_transform(uint32_t state);

/**
 * D_transform: corner phase check for D move
 * corners: 4567 => 4675
 *
 * This function transforms the corner phase for the D move. It takes the
 * 32-bit representation of the corner phase as input and returns the
 * transformed corner phase as a uint32_t.
 *
 * @state:                      32-bit representation of corner phase
 * @return:                     transformed corner phase
 */
uint32_t D_transform(uint32_t state);

/**
 * DPrime_transform: corner phase check for D' move
 * corners: 4567 => 5746
 *
 * This function transforms the corner phase for the D' move. It takes the
 * 32-bit representation of the corner phase as input and returns the
 * transformed corner phase as a uint32_t.
 *
 * @state:                      32-bit representation of corner phase
 * @return:                     transformed corner phase
 */
uint32_t DPrime_transform(uint32_t state);

/**
 * D2_transform: corner phase check for D2 move
 * corners: 4567 => 7564
 *
 * This function transforms the corner phase for the D2 move. It takes the
 * 32-bit representation of the corner phase as input and returns the
 * transformed corner phase as a uint32_t.
 *
 * @state:                      32-bit representation of corner phase
 * @return:                     transformed corner phase
 */
uint32_t D2_transform(uint32_t state);

/**
 * Uw_transform: Uw phase check for Uw move
 * 
 * @state:                      32-bit representation of Uw phase
 * @return:                     transformed Uw phase
 *
 * This function transforms the Uw phase for the Uw move. It takes the
 * 32-bit representation of the Uw phase as input and returns the
 * transformed Uw phase as a uint32_t.
 */
uint32_t Uw_transform(uint32_t state);

/**
 * UwPrime_transform: Uw phase check for Uw' move
 *
 * This function transforms the Uw phase for the Uw' move. It takes the
 * 32-bit representation of the Uw phase as input and returns the
 * transformed Uw phase as a uint32_t.
 * 
 * @state:                      32-bit representation of Uw phase
 * @return:                     transformed Uw phase
 *
 */
uint32_t UwPrime_transform(uint32_t state);

/**
 * Uw2_transform: Uw phase check for Uw2 move
 * @state:                      32-bit representation of Uw phase
 * @return:                     transformed Uw phase
 *
 * This function transforms the Uw phase for the Uw2 move. It takes the
 * 32-bit representation of the Uw phase as input and returns the
 * transformed Uw phase as a uint32_t.
 */
uint32_t Uw2_transform(uint32_t state);

/**
 * Dw_transform: Dw phase check for Dw move
 * 
 * This function transforms the Dw phase for the Dw move. It takes the
 * 32-bit representation of the Dw phase as input and returns the
 * transformed Dw phase as a uint32_t.
 *
 * @state:                      32-bit representation of Dw phase
 * @return:                     transformed Dw phase
 */
uint32_t Dw_transform(uint32_t state);

/**
 * DwPrime_transform: Dw phase check for Dw' move
 * 
 * This function transforms the Dw phase for the Dw' move. It takes the
 * 32-bit representation of the Dw phase as input and returns the
 * transformed Dw phase as a uint32_t.
 *
 * @state:                      32-bit representation of Dw phase
 * @return:                     transformed Dw phase
 */
uint32_t DwPrime_transform(uint32_t state);

/**
 * Dw2_transform: Dw phase check for Dw2 move
 *
 * This function transforms the Dw phase for the Dw2 move. It takes the
 * 32-bit representation of the Dw phase as input and returns the
 * transformed Dw phase as a uint32_t.
 *
 * @state:                      32-bit representation of Dw phase
 * @return:                     transformed Dw phase
 */
uint32_t Dw2_transform(uint32_t state);

// edge phase check

/**
 * Swaps two bits in a byte at specified positions.
 * 
 * This function takes a byte and swaps the bits at the given
 * positions if they are different. The positions are specified
 * by the parameters `m` and `n`. If the bits are the same,
 * the byte remains unchanged.
 * 
 * @param x                     The byte in which bits are to be swapped.
 * @param m                     The position of the first bit to swap.
 * @param n                     The position of the second bit to swap.
 * @return                      The byte with the bits swapped, if they were different.
 */

uint8_t swap_bits(uint8_t x, uint8_t m, uint8_t n);

/**
 * edge_E_transform: edge phase check for E move
 * @state:                      8-bit representation of edge phase
 * @return:                     transformed edge phase
 *
 * This function transforms the edge phase for the E move. It takes the
 * 8-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint8_t.
 */
uint8_t edge_E_transform(uint8_t state);

/**
 * edge_EPrime_transform: edge phase check for E' move
 * @state:                      8-bit representation of edge phase
 * @return:                     transformed edge phase
 *
 * This function transforms the edge phase for the E' move. It takes the
 * 8-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint8_t.
 */
uint8_t edge_EPrime_transform(uint8_t state);

/**
 * edge_E2_transform: edge phase check for E2 move
 * @state:                      8-bit representation of edge phase
 * @return:                     transformed edge phase
 *
 * This function transforms the edge phase for the E2 move. It takes the
 * 8-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint8_t.
 */
uint8_t edge_E2_transform(uint8_t state);

/**
 * edge_F_transform: edge phase check for F move
 * @state:                      8-bit representation of edge phase
 * @return:                     transformed edge phase
 *
 * This function transforms the edge phase for the F move. It takes the
 * 8-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint8_t.
 */
uint8_t edge_F_transform(uint8_t state);

/**
 * edge_L_transform: edge phase check for L move
 * @state:                      8-bit representation of edge phase
 * @return:                     transformed edge phase
 *
 * This function transforms the edge phase for the L move. It takes the
 * 8-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint8_t.
 */

uint8_t edge_L_transform(uint8_t state);

/**
 * edge_B_transform: edge phase check for B move
 * @state:                      8-bit representation of edge phase
 * @return:                     transformed edge phase
 *
 * This function transforms the edge phase for the B move. It takes the
 * 8-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint8_t.
 */
uint8_t edge_B_transform(uint8_t state);

/**
 * edge_R_transform: edge phase check for R move
 * @state:                      8-bit representation of edge phase
 * @return:                     transformed edge phase
 *
 * This function transforms the edge phase for the R move. It takes the
 * 8-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint8_t.
 */
uint8_t edge_R_transform(uint8_t state);

extern const Move R;
extern const Move L;
extern const Move F;
extern const Move B;
extern const Move U;
extern const Move UPrime;
extern const Move U2;
extern const Move E;
extern const Move EPrime;
extern const Move E2;
extern const Move D;
extern const Move DPrime;
extern const Move D2;
extern const Move Uw;
extern const Move UwPrime;
extern const Move Uw2;
extern const Move Dw;
extern const Move DwPrime;
extern const Move Dw2;
extern const Move EMPTY;

#endif