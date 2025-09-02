#ifndef MY_UTILS_H
#define MY_UTILS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Convert an integer to a string in a given base. The function modifies the
 * given string to store the result. The result is stored in reverse order, so
 * the resulting string is reversed at the end of the function.
 *
 * @param num The integer to convert.
 * @param str The string to modify and store the result in.
 * @param base The base to use for the conversion.
 */
void my_itoa(int num, char* str, int base);

/**
 * Reads the contents of a file into a given string. The string is not
 * necessarily null-terminated, but the last character will be set to '\0' to
 * make it null-terminated.
 *
 * @param result The string to store the result in.
 * @param file_path The path to the file to read from.
 */
void read_from_file(char* result, const char* file_path);

/**
 * Checks if a state is one of the original states.
 *
 * This function takes the current state and an array of original states, and
 * checks if the current state is one of the original states. If the current
 * state is one of the original states, the function returns true; otherwise, it
 * returns false.
 *
 * @param state             The current state to check.
 * @param original_state    An array of original states to check against.
 *
 * @return                      True if the current state is an original state, false otherwise.
 */

bool is_original_state(int state, const int* original_state);

/**
 * Checks if a command-line argument is present.
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
bool has_argv(int argc, char const *argv[], const char* key1, const char* key2);

/**
 * Returns the current time in milliseconds since the Epoch (January 1, 1970).
 *
 * This function is used to measure the time taken to solve a cube.
 *
 * @return                      The current time in milliseconds.
 */
uint64_t get_current_time();


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
const char* get_argv(int argc, char const *argv[], const char* key1, const char* key2);

#endif