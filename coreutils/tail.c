#include <stdio.h>            // fprintf(), printf(), putchar(), snprintf(), fopen(), fclose()
#include <stdlib.h>           // malloc(), strtol(), strtof()
#include <string.h>           // strcmp(), strlen(), strcpy()
#include <getopt.h>           // getopt(), optarg, optind, optopt
#include "../include/util.h"  // print_error(), perror2(), da_append(), da_destroy(), getline()

typedef struct {
    char   **data;
    size_t count;
    size_t capacity;
} da_lines;

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [-f] [-s float] [-n int] [-v|-q]\n", program);
}

int main(int argc, char* argv[])
{
    const char* program = argv[0];

    char mode = 'n';
    long num = 10;               // default: -n10
    int verbosity = 1;           // quiet:0 normal:1 full:2
    int fflag = 0;               // follow file output
    float sleep_interval = 1.0f; // in seconds

    // TODO tail -f, make use of -s
    (void)fflag;
    (void)sleep_interval;

    char* endptr;
    int opt;
    while((opt = getopt(argc, argv, ":n:s:fqv")) != -1) {
        switch(opt) {
            case 'c': // fallthrough
            case 'n':
                mode = (char)opt;
                num = strtol(optarg, &endptr, 10);
                if(endptr == optarg) {
                    print_error("%s: %s: not an integer", program, optarg);
                    return 1;
                }
                break;
            case 's':
                sleep_interval = strtof(optarg, &endptr);
                if(endptr == optarg) {
                    print_error("%s: %s: not a floating point number", program, optarg);
                    return 1;
                }
                break;
            case 'f':
                fflag = 1;
                break;
            case 'q':
                verbosity = 0;
                break;
            case 'v':
                verbosity = 2;
                break;
            case '?':
                print_error("%s: invalid option -- '%c'", program, optopt);
                print_usage(program);
                return 1;
                break;
            case ':':
                print_error("%s: option '%c' needs an argument", program, optopt);
                print_usage(program);
                return 1;
                break;
        }
    }

    argc -= optind;
    argv += optind - 1;

    if(argc == 0) {
        argv--;
        argv[1] = "-";
    }

    FILE* fp;
    while(*++argv) {
        fp = stdin;
        if(strcmp(*argv, "-"))
            fp = fopen(*argv, "r");

        if(fp == NULL) {
            char errstring[150] = {0};
            snprintf(errstring, sizeof(errstring), "could not open file %s", *argv);
            perror2(errstring, program);
            return 1;
        }

        if(verbosity == 2)
            printf("==> %s <==\n", (fp == stdin) ? "standard input" : *argv);

        if(mode == 'c') {
            long i = 0;
            int c;
            while((c = fgetc(fp)) != EOF) {
                if(i > num) putchar(c);
                i++;
            }
        } else {
            da_lines lines = {0};
            size_t cap = 0;
            char* line = NULL;
            while(getline(&line, &cap, fp) != -1) {
                char* line2 = malloc(strlen(line) + 1);
                if(line2 == NULL) {
                    perror2("malloc", program);
                    return 2;
                }
                strcpy(line2, line);
                da_append(&lines, line2);
            }
            size_t n_lines = lines.count;
            for(size_t i = n_lines - num; i < n_lines; i++)
                printf("%s", lines.data[i]);
            da_destroy(&lines);
        }

        if(fp != stdin) fclose(fp);
        if(argc >= 2)   putchar('\n');
    }

    return 0;
}
