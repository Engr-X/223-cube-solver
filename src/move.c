#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <immintrin.h>

#include "move.h"

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
uint32_t R_transform(uint32_t state)
{
    uint32_t c2 = state >> 23 & 0b111;
    uint32_t c3 = state >> 20 & 0b111;
    uint32_t c6 = state >> 11 & 0b111;
    uint32_t c7 = state >> 8 & 0b111;

    uint32_t e2 = state >> 2 & 0b11;
    uint32_t e3 = state & 0b11;

    state &= ~(0b111 << 23 | 0b111 << 20 | 0b111 << 11 | 0b111 << 8 | 0b11 << 2 | 0b11);
    state |= c7 << 23 | c6 << 20 | c3 << 11 | c2 << 8 | e3 << 2 | e2;

    return state;
}

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
uint32_t L_transform(uint32_t state)
{
    uint32_t c0 = state >> 29 & 0b111;
    uint32_t c1 = state >> 26 & 0b111;
    uint32_t c4 = state >> 17 & 0b111;
    uint32_t c5 = state >> 14 & 0b111;

    uint32_t e0 = state >> 6 & 0b11;
    uint32_t e1 = state >> 4 & 0b11;

    state &= ~(0b111 << 29 | 0b111 << 26 | 0b111 << 17 | 0b111 << 14 | 0b11 << 6 | 0b11 << 4);
    state |= c5 << 29 | c4 << 26 | c1 << 17 | c0 << 14 | e1 << 6 | e0 << 4;

    return state;
}

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
uint32_t F_transform(uint32_t state)
{
    uint32_t c0 = state >> 29 & 0b111;
    uint32_t c3 = state >> 20 & 0b111;
    uint32_t c4 = state >> 17 & 0b111;
    uint32_t c7 = state >> 8 & 0b111;

    uint32_t e0 = state >> 6 & 0b11;
    uint32_t e3 = state & 0b11;

    state &= ~(0b111 << 29 | 0b111 << 20 | 0b111 << 17 | 0b111 << 8 | 0b111 << 6 | 0b11);
    state |= c7 << 29 | c4 << 20 | c3 << 17 | c0 << 8 | e3 << 6 | e0;

    return state;
}

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
uint32_t B_transform(uint32_t state)
{
    uint32_t c1 = state >> 26 & 0b111;
    uint32_t c2 = state >> 23 & 0b111;
    uint32_t c5 = state >> 14 & 0b111;
    uint32_t c6 = state >> 11 & 0b111;

    uint32_t e1 = state >> 4 & 0b11;
    uint32_t e2 = state >> 2 & 0b11;

    state &= ~(0b111 << 26 | 0b111 << 23 | 0b111 << 14 | 0b111 << 11 | 0b11 << 4 | 0b11 << 2);
    state |= c6 << 26 | c5 << 23 | c2 << 14 | c1 << 11 | e2 << 4 | e1 << 2;
    return state;
}

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
uint32_t U_transform(uint32_t state)
{
    uint16_t t = state >> 20;  
    t = t >> 3 | t << 9; 
    t &= 0xfff;
    return (state & 0x000fffff) | t << 20;
}

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
uint32_t UPrime_transform(uint32_t state)
{
    uint16_t t = state >> 20;
    t = t << 3 | t >> 9;
    t &= 0xfff;
    return (state & 0x000fffff) | t << 20;
}

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
uint32_t U2_transform(uint32_t state)
{
    uint16_t t = state >> 20;
    t = t << 6 | t >> 6;
    t &= 0xfff;
    return (state & 0x000fffff) | t << 20;
}

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
uint32_t E_transform(uint32_t state)
{
    uint8_t t = state & 0xff;
    t = t >> 2 | t << 6;
    return (state & 0xffffff00) | t;
}

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
uint32_t EPrime_transform(uint32_t state)
{
    uint8_t t = state & 0xff;
    t = t << 2 | t >> 6;
    return (state & 0xffffff00) | t;
}

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
uint32_t E2_transform(uint32_t state)
{
    uint8_t t = state & 0xff;
    t = t << 4 | t >> 4;
    return (state & 0xffffff00) | t;
}

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
uint32_t D_transform(uint32_t state)
{
    uint16_t t = ((state >> 8) & 0xfff);
    t = t << 3 | t >> 9;
    t &= 0xfff;
    return (state & ~(0xfff << 8)) | t << 8;
}

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
uint32_t DPrime_transform(uint32_t state)
{
    uint16_t t = ((state >> 8) & 0xfff);
    t = t >> 3 | t << 9;
    t &= 0xfff;
    return (state & ~(0xfff << 8)) | t << 8;
}

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
uint32_t D2_transform(uint32_t state)
{
    uint16_t t = ((state >> 8) & 0xfff);
    t = t << 6 | t >> 6;
    t &= 0xfff;
    return (state & ~(0xfff << 8)) | t << 8;
}

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
uint32_t Uw_transform(uint32_t state)
{
    // corner transform
    uint16_t t1 = state >> 20;
    t1 = t1 >> 3 | t1 << 9;
    t1 &= 0xfff;

    // edge transform
    uint8_t t2 = state & 0xff;
    t2 = t2 >> 2 | t2 << 6;

    return (state & 0x000fff00) | t1 << 20 | t2;
}

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
uint32_t UwPrime_transform(uint32_t state)
{
    // corner transform
    uint16_t t1 = state >> 20;
    t1 = t1 << 3 | t1 >> 9;
    t1 &= 0xfff;

    // edge transform
    uint8_t t2 = state & 0xff;
    t2 = t2 << 2 | t2 >> 6;

    return (state & 0x000fff00) | t1 << 20 | t2;
}

/**
 * Uw2_transform: Uw phase check for Uw2 move
 * 
 * @state:                      32-bit representation of Uw phase
 * @return:                     transformed Uw phase
 *
 * This function transforms the Uw phase for the Uw2 move. It takes the
 * 32-bit representation of the Uw phase as input and returns the
 * transformed Uw phase as a uint32_t.
 */
uint32_t Uw2_transform(uint32_t state)
{
    // corner transform
    uint16_t t1 = state >> 20;
    t1 = t1 << 6 | t1 >> 6;
    t1 &= 0xfff;

    // edge transform
    uint8_t t2 = state & 0xff;
    t2 = t2 << 4 | t2 >> 4;

    return (state & 0x000fff00) | t1 << 20 | t2;
}

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
uint32_t Dw_transform(uint32_t state)
{
    // corner transform
    uint16_t t1 = ((state >> 8) & 0xfff);
    t1 = t1 << 3 | t1 >> 9;
    t1 &= 0xfff;
    
    // edge transform
    uint8_t t2 = state & 0xff;
    t2 = t2 << 2 | t2 >> 6;

    return (state & ~0xfffff) | t1 << 8 | t2;
}

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
uint32_t DwPrime_transform(uint32_t state)
{
    // corner transform
    uint16_t t1 = ((state >> 8) & 0xfff);
    t1 = t1 >> 3 | t1 << 9;
    t1 &= 0xfff;

    // edge transform
    uint8_t t2 = state & 0xff;
    t2 = t2 >> 2 | t2 << 6;

    return (state & ~0xfffff) | t1 << 8 | t2;
}

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
uint32_t Dw2_transform(uint32_t state)
{
    // corner transform
    uint16_t t1 = ((state >> 8) & 0xfff);
    t1 = t1 << 6 | t1 >> 6;
    t1 &= 0xfff;

    // edge transform
    uint8_t t2 = state & 0xff;
    t2 = t2 << 4 | t2 >> 4;

    return (state & ~0xfffff) | t1 << 8 | t2;
}

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

uint8_t swap_bits(uint8_t x, uint8_t m, uint8_t n)
{
    const uint8_t bit_m = (x >> m) & 1;
    const uint8_t bit_n = (x >> n) & 1;

    if (bit_m != bit_n)
    {
        uint8_t mask = (1 << m) | (1 << n);
        x ^= mask;
    }

    return x;
}

/**
 * edge_E_transform: edge phase check for E move
 * 
 * @state:                      8-bit representation of edge phase
 * @return:                     transformed edge phase
 *
 * This function transforms the edge phase for the E move. It takes the
 * 8-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint8_t.
 */
uint8_t edge_E_transform(uint8_t state)
{
    return state << 2 | state >> (8 - 2);
}

/**
 * edge_EPrime_transform: edge phase check for E' move
 * 
 * @state:                      8-bit representation of edge phase
 * @return:                     transformed edge phase
 *
 * This function transforms the edge phase for the E' move. It takes the
 * 8-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint8_t.
 */
uint8_t edge_EPrime_transform(uint8_t state)
{
    return state >> 2 | state << (8 - 2);
}

/**
 * edge_E2_transform: edge phase check for E2 move
 * 
 * @state:                      8-bit representation of edge phase
 * @return:                     transformed edge phase
 *
 * This function transforms the edge phase for the E2 move. It takes the
 * 8-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint8_t.
 */
uint8_t edge_E2_transform(uint8_t state)
{
    return state << 4 | state >> (8 - 4);
}

/**
 * edge_F_transform: edge phase check for F move
 * 
 * @state:                      8-bit representation of edge phase
 * @return:                     transformed edge phase
 *
 * This function transforms the edge phase for the F move. It takes the
 * 8-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint8_t.
 */
uint8_t edge_F_transform(uint8_t state)
{
    return swap_bits(swap_bits(state, 0, 1), 2, 7);
}

/**
 * edge_L_transform: edge phase check for L move
 * 
 * @state:                      8-bit representation of edge phase
 * @return:                     transformed edge phase
 *
 * This function transforms the edge phase for the L move. It takes the
 * 8-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint8_t.
 */

uint8_t edge_L_transform(uint8_t state)
{
    return swap_bits(swap_bits(state, 2, 3), 1, 4);
}

/**
 * edge_B_transform: edge phase check for B move
 * 
 * @state:                      8-bit representation of edge phase
 * @return:                     transformed edge phase
 *
 * This function transforms the edge phase for the B move. It takes the
 * 8-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint8_t.
 */
uint8_t edge_B_transform(uint8_t state)
{
    return swap_bits(swap_bits(state, 4, 5), 3, 6);
}

/**
 * edge_R_transform: edge phase check for R move
 * 
 * @state:                      8-bit representation of edge phase
 * @return:                     transformed edge phase
 *
 * This function transforms the edge phase for the R move. It takes the
 * 8-bit representation of the edge phase as input and returns the
 * transformed edge phase as a uint8_t.
 */
uint8_t edge_R_transform(uint8_t state)
{
    return swap_bits(swap_bits(state, 6, 7), 5, 0);
}

const Move R = {.serial = 0, .symbol = "R\0", .transform = R_transform};
const Move L = {.serial = 1, .symbol = "L\0", .transform = L_transform};
const Move F = {.serial = 2, .symbol = "F\0", .transform = F_transform};
const Move B = {.serial = 3, .symbol = "B\0", .transform = B_transform};

const Move U = {.serial = 4, .symbol = "U\0", .transform = U_transform};
const Move UPrime = {.serial = 5, .symbol = "U'\0", .transform = UPrime_transform};
const Move U2 = {.serial = 6, .symbol = "U2\0", .transform = U2_transform};

const Move E = {.serial = 7, .symbol = "E\0", .transform = E_transform};
const Move EPrime = {.serial = 8, .symbol = "E'\0", .transform = EPrime_transform};
const Move E2 = {.serial = 9, .symbol = "E2\0", .transform = E2_transform};

const Move D = {.serial = 10, .symbol = "D\0", .transform = D_transform};
const Move DPrime = {.serial = 11, .symbol = "D'\0", .transform = DPrime_transform};
const Move D2 = {.serial = 12, .symbol = "D2\0", .transform = D2_transform};

const Move Uw = {.serial = 13, .symbol = "Uw\0", .transform = Uw_transform};
const Move UwPrime = {.serial = 14, .symbol = "Uw'\0", .transform = UwPrime_transform};
const Move Uw2 = {.serial = 15, .symbol = "Uw2\0", .transform = Uw2_transform};

const Move Dw = {.serial = 16, .symbol = "Dw\0", .transform = Dw_transform};
const Move DwPrime = {.serial = 17, .symbol = "Dw'\0", .transform = DwPrime_transform};
const Move Dw2 = {.serial = 18, .symbol = "Dw2\0", .transform = Dw2_transform};

const Move EMPTY = {.serial = -1, .symbol = "NaN\0", NULL};