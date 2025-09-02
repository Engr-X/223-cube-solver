#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <cJSON.h>

#include "utils.h"
#include "cube_solver.h"

/**
 * Benchmark all moves of the rubik cube.
 *
 * It will benchmark each move by calling the move function 1 billion times and
 * measure the time it takes. The result will be printed out in seconds for each
 * move.
 */
void bench_mark()
{
    // all move
    const Move ALL_MOVES[19] = {R, L, F, B, U, UPrime, U2, E, EPrime, E2, D, DPrime, D2, Uw, UwPrime, Uw2, Dw, DwPrime, Dw2};

    // default initial state
    uint32_t number;

    // loop for every function
    for (uint8_t i = 0; i < sizeof(ALL_MOVES) / sizeof(ALL_MOVES[0]); i++)
    {
        number = rand();
        const Move move = ALL_MOVES[i];

        uint64_t current_time = get_current_time();

        // run for 1 billion times
        for (uint64_t i = 0; i < 1e9; i++)
            number = move.transform(number);

        printf("move: %s, time: %lf (s / 1 billion times call)\n", move.symbol, (get_current_time() - current_time) / 1000.0);
    }
}

/**
 * The main entry point of the program.
 *
 * The main function of the program.
 *
 * @param argc                  The number of arguments passed to the program.
 * @param argv                  The arguments passed to the program.
 *
 * @return The exit status of the program.
 */
int main(int argc, char const *argv[])
{
    srand(time(NULL));

    if (has_argv(argc, argv, "-h", "--help"))
    {
        printf("Usage: 233solver [options]\n\n");

        printf("Options:\n");
        printf("  -h, --help          Show this help message and exit.\n");
        printf("  -v, --version       Display the version information.\n");
        printf("  -b, --bench         Run benchmark tests to measure performance.\n");
        printf("  -f, --file <path>   Specify the path to the settings JSON file (default: settings.json).\n");

        // 可以补充更多参数的说明
        printf("\nExamples:\n");
        printf("  233solver -h           Show the help message.\n");
        printf("  233solver -v           Show version info.\n");
        printf("  233solver -b           Run performance benchmarks.\n");
        printf("  233solver -f [File Path]  Solve the cube using the specified settings file.\n");
        return 0;
    }

    if (has_argv(argc, argv, "-v", "--version"))
    {
        puts("233solver version 1.0.0 (x86_64-win32-seh-rev0, Built by MinGW 13.2.0 project)");
        return 0;
    }

    if (has_argv(argc, argv, "-b", "--bench"))
    {
        bench_mark();
        return 0;
    }

    if (has_argv(argc, argv, "-f", "--file"))
    {
        char res[2048] = "\0";
        char* file_path = (char*)(get_argv(argc, argv, "-f", "--file"));

        if (file_path == NULL)
            file_path = "settings.json\0";

        read_from_file(res, file_path);
        cJSON* json = cJSON_Parse(res);

        // solve cube
        cube_solver(json); 
        cJSON_Delete(json);
    }
    else
        puts("Hello, world! from 233solver witten by Di Wang");
    
    return 0;
}