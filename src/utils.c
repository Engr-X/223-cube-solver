#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#include "utils.h"

/**
 * Convert an integer to a string in a given base. The function modifies the
 * given string to store the result. The result is stored in reverse order, so
 * the resulting string is reversed at the end of the function.
 *
 * @param num The integer to convert.
 * @param str The string to modify and store the result in.
 * @param base The base to use for the conversion.
 */
void my_itoa(int num, char* str, int base)
{
    int i = 0;
    int is_negative = 0;

    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (num < 0 && base == 10)
    {
        is_negative = 1;
        num = -num;
    }

    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    if (is_negative)
        str[i++] = '-';

    str[i] = '\0';

    int start = 0;
    int end = i - 1;

    while (start < end)
    {
        const char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

/**
 * Reads the contents of a file into a given string. The string is not
 * necessarily null-terminated, but the last character will be set to '\0' to
 * make it null-terminated.
 *
 * @param result The string to store the result in.
 * @param file_path The path to the file to read from.
 */
void read_from_file(char* result, const char* file_path)
{
    FILE* file = fopen(file_path, "r");

    if (!file)
    {
        printf("Error opening file: %s\n", file_path);
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    size_t bytes_read = fread(result, 1, file_size, file);
    result[bytes_read] = '\0';
    fclose(file);
}

/**
 *                       Checks if a state is one of the original states.
 *
 * This function takes the current state and an array of original states, and
 * checks if the current state is one of the original states. If the current
 * state is one of the original states, the function returns true; otherwise, it
 * returns false.
 *
 * @param state             The current state to check.
 * @param original_state    An array of original states to check against (ranked).
 *
 * @return                      True if the current state is an original state, false otherwise.
 */

bool is_original_state(int state, const int* original_state)
{
    if (state > 0)
        return state > original_state[6] ? (state == original_state[6]) || (state == original_state[7]) :
                                           (state == original_state[4]) || (state == original_state[5]);
    else
        return state > original_state[3] ? (state == original_state[3]) || (state == original_state[4]) :
                                           (state == original_state[0]) || (state == original_state[1]);
    
    return false;
}

/**
 *                           Checks if a command-line argument is present.
 *
 * This function takes the command-line arguments passed to main and checks if
 * either of the two given keys is present.
 *
 * @param argc                The number of command-line arguments.
 * @param argv                The array of command-line arguments.
 * @param key1                The first key to search for.
 * @param key2                The second key to search for.
 *
 * @return                         True if either key is found, false otherwise.
 */
bool has_argv(int argc, char const *argv[], const char* key1, const char* key2)
{
    for (uint8_t i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], key1) == 0 ||
            strcmp(argv[i], key2) == 0)
            return true;
    }

    return false;
}

/**
 * Returns the current time in milliseconds since the Epoch (January 1, 1970).
 *
 * This function is used to measure the time taken to solve a cube.
 *
 * @return                      The current time in milliseconds.
 */
uint64_t get_current_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

/**
 * Returns the value of a command-line argument.
 *
 * This function takes the command-line arguments passed to main and checks if
 * either of the two given keys is present. If either key is found, the function
 * returns the value of the argument (i.e. the string after the key). If neither
 * key is found, the function returns NULL.
 *
 * @param argc                The number of command-line arguments.
 * @param argv                The array of command-line arguments.
 * @param key1                The first key to search for.
 * @param key2                The second key to search for.
 *
 * @return                    The value of the argument, or NULL if not found.
 */
const char* get_argv(int argc, char const *argv[], const char* key1, const char* key2)
{
    for (int i = 0; i < argc; i++)
    {
        if ((strcmp(argv[i], key1) == 0 && i + 1 < argc) ||
            (strcmp(argv[i], key2) == 0 && i + 1 < argc))
            return argv[i + 1];
    }

    return NULL;
}