#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/prettyprint.h"

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [-pv] dir [dir2] [dir3] ...\n", program);
}

int main(int argc, char* argv[])
{
    const char* program = argv[0];

    int pflag = 0; // remove directories recursively
    int vflag = 0; // show operations / verbose mode

    int opt;
    while((opt = getopt(argc, argv, ":pv")) != -1) {
        switch(opt) {
            case 'v':
                vflag = 1;
                break;
            case 'p':
                pflag = 1;
                break;
            case '?':
                print_error("%s: option error: unknown option \"-%c\"", program, optopt);
                print_usage(program);
                return 1;
                break;
        }
    }

    if(optind == argc) {
        print_usage(program);
        return 1;
    }
    optind--;

    argv += optind;
    if(!argv[0]) { // no non-option argument is provided
        print_usage(program);
        return 1;
    }

    // TODO implement rmdir -p
    (void)pflag;
    int excode = 0;
    while(*++argv) {
        if(rmdir(*argv) == -1) {
            char errstring[150] = {0};
            snprintf(errstring, sizeof(errstring), "removing directory '%s' failed", *argv);
            perror2(errstring, program);
            excode = 1;
            break;
        }
        if(vflag)
            printf("%s: removing directory '%s'\n", program, *argv);
    }

    return excode;
}
