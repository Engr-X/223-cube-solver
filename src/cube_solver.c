#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "cube_solver.h"
#include "bfs_solver.h"
#include "dfs_solver.h"

/**
 *                       Converts a cube state to a human-readable string.
 *
 * This function takes a cube state represented as a 32-bit unsigned integer and
 * converts it to a human-readable string. The string is formatted as a 3x3x2
 * matrix of strings, where each string represents a color and position of a
 * corner or edge of the cube.
 *
 * @param result                The string to store the result in.
 * @param state                 The cube state to convert.
 */
void cube_state(char* result, uint32_t state)
{
    char cornersState[25] = "\n", edgesState[9] = "\n";
    my_itoa(state >> 8, cornersState, 2);
    my_itoa(state & 0xff, edgesState, 2);

    while (true)
    {
        const uint8_t size = strlen(cornersState);

        if (size < 24)
        {
            memmove(cornersState + 1, cornersState, (size + 1 * sizeof(char)));
            cornersState[0] = '0';
        }
        else
            break;
    }

    while (true)
    {
        const uint8_t size = strlen(edgesState);

        if (size < 8)
        {
            memmove(edgesState + 1, edgesState, (size + 1 * sizeof(char)));
            edgesState[0] = '0';
        }
        else
            break;
    }

    char arr[3][2][2][4] = {{{"NaN\n", "NaN\n"}, {"NaN\n", "NaN\n"}}, {{"NaN\n", "NaN"}, {"NaN\n", "NaN\n"}}, {{"NaN\n", "NaN\n"}, {"NaN\n", "NaN\n"}}};

    for (uint8_t i = 0; i < 8; i++)
    {
        const uint8_t index = i < 4 ? 0 : 2;
        char part[4];

        memcpy(part, cornersState + i * 3, 3 * sizeof(char));
        part[3] = '\0';

        if (strcmp(part, "000") == 0) strcpy(part, "YBO");
        else if (strcmp(part, "001") == 0) strcpy(part, "YOG");
        else if (strcmp(part, "010") == 0) strcpy(part, "YGR");
        else if (strcmp(part, "011") == 0) strcpy(part, "YRB");
        else if (strcmp(part, "100") == 0) strcpy(part, "WOB");
        else if (strcmp(part, "101") == 0) strcpy(part, "WGO");
        else if (strcmp(part, "110") == 0) strcpy(part, "WRG");
        else if (strcmp(part, "111") == 0) strcpy(part, "WBR");

        switch (i % 4)
        {
            case 0: {strcpy(arr[index][1][0], part); break;}
            case 1: {strcpy(arr[index][0][0], part); break;}
            case 2: {strcpy(arr[index][0][1], part); break;}
            case 3: {strcpy(arr[index][1][1], part); break;}
            default: break;
        }
    }

    for (uint8_t i = 0; i < 4; i++)
    {
        char part[3];
        memcpy(part, edgesState + i * 2, 2 * sizeof(char));
        part[2] = '\0';

        if (strcmp(part, "00") == 0) strcpy(part, "BO");
        else if (strcmp(part, "01") == 0) strcpy(part, "GO");
        else if (strcmp(part, "10") == 0) strcpy(part, "GR");
        else if (strcmp(part, "11") == 0) strcpy(part, "BR");

        switch (i % 4)
        {
            case 0: {strcpy(arr[1][1][0], part); break;}
            case 1: {strcpy(arr[1][0][0], part); break;}
            case 2: {strcpy(arr[1][0][1], part); break;}
            case 3: {strcpy(arr[1][1][1], part); break;}
            default: break;
        }
    }

    char result_string[1024] = "\0"; 

    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 2; j++)
        {
            for (uint8_t k = 0; k < 2; k++)
            {
                strcat(result_string, arr[i][j][k]);
                strcat(result_string, " ");
            }

            strcat(result_string, "\n");
        }

        strcat(result_string, "\n");
    }

    printf("Cube: \n%s", result_string);

    if (result != NULL)
        strcpy(result, result_string);
}

/**
 *                       Converts a cube state represented as two arrays of 8 and 4 bytes
 *                               respectively to a single 32-bit unsigned integer.
 *
 * This function takes a cube state represented as two arrays of 8 bytes for corners and 4 bytes
 * for edges and converts it to a single 32-bit unsigned integer. The integer is formatted as
 * follows: the first 24 bits represent the corners and the last 8 bits represent the edges.
 *
 * @param corners               The array of 8 bytes representing the corners of the cube.
 * @param edges                 The array of 4 bytes representing the edges of the cube.
 * @return                      The 32-bit unsigned integer representation of the cube state.
 */
uint32_t cube_convert(const uint8_t* corners, const uint8_t* edges)
{
    uint32_t result = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        result <<= 3;
        result |= corners[i];
    }

    for (uint8_t i = 0; i < 4; i++)
    {
        result <<= 2;
        result |= edges[i];
    }

    return result;
}

/**
 *                       Converts an edge phase represented as an array of 4 bytes to a
 *                               single 8-bit unsigned integer.
 *
 * This function takes an edge phase represented as an array of 4 bytes and
 * converts it to a single 8-bit unsigned integer.
 *
 * @param edges                 The array of 4 bytes representing the edges of the cube.
 * @return                      The 8-bit unsigned integer representation of the edge phase.
 */
uint8_t edges_phase_convert(const uint8_t* edges)
{
    return 1 << edges[4] | 1 << edges[5];
}

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
void cube_solver(const cJSON* json)
{
    const uint8_t moves_size = 19;
    const Move ALL_MOVES[19] = {R, L, F, B, U, UPrime, U2, E, EPrime, E2, D, DPrime, D2, Uw, UwPrime, Uw2, Dw, DwPrime, Dw2};
    int CORNOR_ORIGINAL_STATES[8] = {};
    const int ALL_ORIGINAL_STATES[8] = {-1622093511, -1277027762, -697023597, -87652124, 87652123, 697023596, 1277027761, 1622093510};

    for (int8_t i = 0; i < sizeof(ALL_ORIGINAL_STATES) / sizeof(ALL_ORIGINAL_STATES[0]); i++)
        CORNOR_ORIGINAL_STATES[i] = ALL_ORIGINAL_STATES[i] & 0xffffff00;

    const cJSON* max_depth_json = cJSON_GetObjectItemCaseSensitive(json, "max_depth");

    if (max_depth_json == NULL)
    {
        printf("Invalid json format: max_depth not found\n");
        return;
    }

    const cJSON* min_depth_json = cJSON_GetObjectItemCaseSensitive(json, "min_depth");

    if (min_depth_json == NULL)
    {
        printf("Invalid json format: min_depth not found\n");
        return;
    }

    const cJSON* corners_array_json = cJSON_GetObjectItemCaseSensitive(json, "corners");

    if (corners_array_json == NULL)
    {
        printf("Invalid json format: corners not found\n");
        return;
    }

    const cJSON* edges_array_json = cJSON_GetObjectItemCaseSensitive(json, "edges");

    if (edges_array_json == NULL)
    {
        printf("Invalid json format: edges not found\n");
        return;
    }

    /*const cJSON* moves_array_json = cJSON_GetObjectItemCaseSensitive(json, "moves");

    if (moves_array_json == NULL)
    {
        printf("Invalid json format: moves not found\n");
        return;
    }*/

    const cJSON* moves_map_array_json = cJSON_GetObjectItemCaseSensitive(json, "moves_map");

    if (moves_map_array_json == NULL)
    {
        printf("Invalid json format: moves_map not found\n");
        return;
    }

    const cJSON* algorithm_json = cJSON_GetObjectItemCaseSensitive(json, "algorithm");

    if (algorithm_json == NULL)
    {
        printf("Invalid json format: algorithm not found\n");
        return;
    }

    const uint8_t max_depth = max_depth_json -> valueint;
    const uint8_t min_depth = min_depth_json -> valueint;
    const char* algorithm = algorithm_json -> valuestring;
    bool algorithm_bfs = true;

    uint8_t corners[8] = {0};
    uint8_t edges[6] = {0};
    Move moves[moves_size] = {};
    Move moves_map[moves_size][moves_size] = {};
    Move moves_map_1d[moves_size * moves_size] = {}; 

    bool edges_all0 = true;

    for (uint8_t i = 0; i < 8; i++)
    {
        cJSON* item = cJSON_GetArrayItem(corners_array_json, i);

        if (item == NULL)
        {
            printf("Invalid json format: corners[%d] not found\n", i);
            return;
        }

        corners[i] = item -> valueint;

        if (i < 6)
        {
            item = cJSON_GetArrayItem(edges_array_json, i);

            if (item == NULL)
            {
                printf("Invalid json format: edges[%d] not found\n", i);
                return;
            }

            edges[i] = item -> valueint;
            edges_all0 &= item -> valueint == 0;
        }
    }

    for (uint8_t i = 0; i < moves_size; i++)
    {
        moves[i] = EMPTY;

        for (uint8_t j = 0; j < moves_size; j++)
        {
            moves_map[i][j] = EMPTY;
            moves_map_1d[i * moves_size + j] = EMPTY;
        }
    }

    for (uint8_t i = 0; i < cJSON_GetArraySize(moves_map_array_json); i++)
    {
        const cJSON* row = cJSON_GetArrayItem(moves_map_array_json, i);
        const cJSON* item = cJSON_GetArrayItem(row, 0);
        const char* value = item -> valuestring;

        for (uint8_t j = 0; j < sizeof(ALL_MOVES) / sizeof(ALL_MOVES[0]); j++)
        {
            if (strcmp(value, "NaN\0") == 0)
                continue;

            if (strcmp(value, ALL_MOVES[j].symbol) == 0)
                moves[ALL_MOVES[j].serial] = ALL_MOVES[j];
        }
    }

    for (int8_t i = 0; i < cJSON_GetArraySize(moves_map_array_json); i++)
    {
        const cJSON* row = cJSON_GetArrayItem(moves_map_array_json, i);

        for (int8_t j = 0; j < cJSON_GetArraySize(row); j++)
        {
            const cJSON* item = cJSON_GetArrayItem(row, j);
            const char* value = item -> valuestring;

            for (uint8_t k = 0; k < moves_size; k++)
            {
                if (strcmp(value, "NaN\0") == 0)
                    continue;

                if (strcmp(value, ALL_MOVES[k].symbol) == 0)
                {
                    moves_map[i][j] = ALL_MOVES[k];
                    moves_map_1d[i * moves_size + j] = ALL_MOVES[k];
                }
            }
        }
    }

    uint8_t first_valid_index = 0;

    for (uint8_t i = 0; i < moves_size; i++)
    {
        if (moves[i].transform != NULL && moves[i].serial > first_valid_index)
            first_valid_index = moves[i].serial;
    }

    const uint8_t moves_bits = first_valid_index == 0 ? 1 : log2(first_valid_index) + 1;
    const uint8_t moves_mask = (1 << moves_bits) - 1;

    char content[1024] = "solve settings: \n\0";

    char separate_line[65] = "\0";

    for (uint8_t i = 0; i < 64; i++)
        strcat(separate_line, "-\0");
    
    strcat(content, separate_line);
    strcat(content, "\n");

    if (strcmp(algorithm, "dfs\0") == 0 || strcmp(algorithm, "DFS\0") == 0)
        algorithm_bfs = false;

    sprintf(content + strlen(content), "algorithm: %s\n", algorithm_bfs ? "BFS" : "DFS");
    sprintf(content + strlen(content), "min depth: %d\n", min_depth);
    sprintf(content + strlen(content), "max depth: %d\n", max_depth);
    strcat(content, "corners: ");

    for (uint8_t i = 0; i < 8; i++)
        sprintf(content + strlen(content), "%d ", corners[i]);

    strcat(content, "\nedges: ");

    for (uint8_t i = 0; i < 6; i++)
        sprintf(content + strlen(content), "%d ", edges[i]);

    strcat(content, "\n");

    sprintf(content + strlen(content), "ignore edges: %s\n", edges_all0 ? "true\0" : "false\0");
    sprintf(content + strlen(content), "moves bits: %d\n", moves_bits);
    sprintf(content + strlen(content), "moves musk: %x\n", moves_mask);
    strcat(content, "\nmoves: ");

    for (uint8_t i = 0; i < moves_size; i++)
        sprintf(content + strlen(content), "%s ", moves[i].symbol);

    strcat(content, "\nmoves_map:\n");

    for (uint8_t i = 0; i < moves_size; i++)
    {
        uint8_t index = 0;

        while (true)
        {
            if (moves_map[i][index].transform == NULL)
                break;
                
            sprintf(content + strlen(content), "%s ", moves_map[i][index].symbol);
            index++;
        }

        strcat(content, "\n");
    }

    uint32_t state = cube_convert((const uint8_t*)(corners), (const uint8_t*)(edges));
    uint8_t edges_phase_state = edges_phase_convert((const uint8_t*)(edges));
    sprintf(content + strlen(content), "\n\ncube_state: %d, phase: %d\n", state, edges_phase_state);
    
    for (uint8_t i = 0; i < 64; i++)
        strcat(content, "-\0");

    const int* original_states = edges_all0 ? CORNOR_ORIGINAL_STATES : ALL_ORIGINAL_STATES;

    puts(content);
    cube_state(NULL, state);
    puts(separate_line);

    if (algorithm_bfs)
        cube_bfs_solver(moves, moves_map_1d, original_states, state, edges_phase_state, min_depth, max_depth);
    else
        cube_dfs_solver(moves, moves_map_1d, original_states, state, edges_phase_state, min_depth, max_depth);
}