#include <stdio.h>           // fprintf(), printf(), fopen(), fclose()
#include <stddef.h>          // size_t
#include <string.h>          // strcpy(), strcmp(), strlen()
#include <stdlib.h>          // malloc()
#include "../include/util.h" // getline(), print_error(), da_append(), da_reverse(), da_destroy()

typedef struct {
    char   **data;
    size_t count;
    size_t capacity;
} da_lines;

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [files...]\n", program);
}

int main(int argc, char* argv[])
{
    const char* program = argv[0];
    shift_args(&argc, &argv);

    if(argc == 1 && !strcmp(*argv, "--help")) {
        print_usage(program);
        return 0;
    }

    // TODO maybe make an unshift_args() at this point
    if(argc == 0) {
        --argv;
        ++argc;
        *argv = "-";
    }

    FILE* fp;
    while(*argv) {
        fp = stdin;
        if(strcmp(*argv, "-"))
            fp = fopen(*argv, "r");

        if(fp == NULL) {
            char errstring[150] = {0};
            snprintf(errstring, sizeof(errstring), "could not open file %s", *argv);
            perror2(errstring, program);
            return 1;
        }

        // compile the list of lines
        da_lines lines = {0};
        char* line = NULL;
        size_t cap = 0;
        while(getline(&line, &cap, fp) != -1) {
            char* line2 = malloc(strlen(line) + 1);
            if(line2 == NULL) {
                perror2("malloc", program);
                return 2;
            }
            strcpy(line2, line);
            da_append(&lines, line2);
        }
        if(fp != stdin)  fclose(fp);

        // reverse the lines
        da_reverse(&lines, char*);

        // print the reversed list
        for(size_t i = 0; i < lines.count; ++i)
            printf("%s", lines.data[i]);

        da_destroy(&lines);
        shift_args(&argc, &argv);
    }
    return 0;
}
