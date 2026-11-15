#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define STB_DS_IMPLEMENTATION
#include "../include/stb_ds.h"

#include "../include/util.h"

// void print_usage(const char* program);
int main(int argc, char* argv[])
{
    const char* program = argv[0];

    if(argc < 2) {
        argv--;
        argv[1] = "-";
    }

    FILE* fp;
    while(*++argv) {
        fp = stdin;
        if(strcmp(*argv, "-"))
            fp = fopen(*argv, "r");

        if(fp == NULL) {
            print_error("%s: %s: could not open file", program, *argv);
            return 1;
        }

        // compile the list of lines
        char** line_list = NULL;
        char* line = NULL;
        size_t cap = 0;
        while(getline(&line, &cap, fp) != -1) {
            char* line2 = malloc(strlen(line) + 1);
            if(line2 == NULL) {
              print_error("%s: malloc() failed", program);
              return 2;
            }
            strcpy(line2, line);
            stbds_arrput(line_list, line2);
        }
        if(fp != stdin) fclose(fp);

        // reverse the lines
        char** rline_list = NULL;
        for(size_t i = 0; i < stbds_arrlenu(line_list); i++)
            stbds_arrins(rline_list, 0, line_list[i]);

        // print the reversed list
        for(size_t i = 0; i < stbds_arrlenu(rline_list); i++)
            printf("%s", rline_list[i]);

        stbds_arrfree(line_list);
        stbds_arrfree(rline_list);
    }
    return 0;
}
