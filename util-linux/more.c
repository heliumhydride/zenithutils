#define  _XOPEN_SOURCE 500    // strdup()
#include <stdio.h>            // printf(), fprintf(), snprintf()
#include <string.h>           // strcmp(), strdup()
#include "../include/util.h"  /* perror2(), shift_args(), da_append(), da_destroy()
                                 getline(), get_termsize(), struct winsize[windows-mingw] */

/*
    TODO how do we know if stdin is being piped into or not?
*/

// TODO move to config.h ?
#define MORE_SEPARATOR "::::::::::::::"

typedef struct {
    char   **data;
    size_t count;
    size_t capacity;
} da_lines;

void print_usage(const char *program)
{
    fprintf(stderr, "usage: %s [file]", program);
}

int main(int argc, char* argv[])
{
    const char *program = *argv;
    shift_args(&argc, &argv);

    if(argc >= 1 && !strcmp(*argv, "--help")) {
        print_usage(program);
        return 0;
    }

    // TODO more from stdin
    FILE* fp = stdin;
    while(*argv) {
        if(argc >= 2) {
            puts(MORE_SEPARATOR);
            puts(*argv);
            puts(MORE_SEPARATOR);
        }

        fp = fopen(*argv, "r");
        if(fp == NULL) {
            char errstring[150] = {0};
            snprintf(errstring, sizeof(errstring), "openning file '%s' failed", *argv);
            perror2(errstring, program);
        }

        // concatenate the lines into an array
        da_lines lines = {0};
        size_t cap = 0;
        char *line = NULL;
        while(getline(&line, &cap, fp) != -1)
            da_append(&lines, strdup(line));

        // TODO if we press space, go forward HEIGHT lines, return go forward a single line
        // page out the lines
        struct winsize ws = get_termsize();
        //for(size_t i = 0; i < lines.count; ++i)
        for(size_t i = 0; i < ws.ws_row; ++i)
            printf(lines.data[i]);

        if(fp != stdin)  fclose(fp);
        da_destroy(&lines);
        shift_args(&argc, &argv);
    }

    return 0;
}
