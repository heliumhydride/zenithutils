#define _XOPEN_SOURCE 500
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/util.h"
#include "../config.h"

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [-fevqn] [file] ...\n", program);
}

int main(int argc, char* argv[])
{
    const char* program = argv[0];

    int qflag = 0; // Quiet mode -- read link, but do not print filename (exit code only)
    int vflag = 0; // Verbose mode -- prints error messages
    int nflag = 0; // No newline
    int fflag = 0; // Canonicalize paths
    int eflag = 0; // Canonicalize paths; path must exist

    int opt;
    while((opt = getopt(argc, argv, ":fevqn")) != -1) {
        switch(opt) {
            case 'f':
                fflag = 1;
                break;
            case 'e':
                fflag = 1;
                eflag = 1;
                break;
            case 'n':
                nflag = 1;
                break;
            case 'v':
                vflag = 1;
                break;
            case 'q':
                qflag = 1;
                break;
            case '?':
                print_error("%s: option error: unknown option '-%c'", program, optopt);
                return 1;
                break;
        }
    }

    // TODO use realpath(...) on Windows
    if(optind == argc) {
        print_usage(program);
        return 1;
    }
    optind--;

    argv += optind;
    if(!argv[0]) { // no non-opt argument is provided
        print_error("%s: path expected", argv[0]);
        print_usage(program);
        return 1;
    }

    // TODO implement -f, -e
    (void)fflag; (void)eflag;
    while(*++argv) {
        char buf[MAX_LINK_LENGTH] = {0};
        if(-1 == readlink(*argv, buf, sizeof(buf))) {
            if(vflag) {
                // TODO error handling
                print_error("%s: '%s': invalid argument", program, *argv);
            }
            return 1;
        } else {
            if(!qflag) {
                puts(buf);
                // TODO ignore -n when multiple arguments are provided
                if(!nflag) putchar('\n');
            }
        }
    }
    return 0;
}
