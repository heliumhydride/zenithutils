#define _POSIX_C_SOURCE 200112L
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "../include/prettyprint.h"

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [-rs] [-p prompt]\n", program);
}

int main(int argc, char* argv[])
{
    const char* program = argv[0];

    char* prompt = NULL;
    int rflag = 0;
    int sflag = 0;

    int opt;
    while((opt = getopt(argc, argv, ":p:rs")) != -1) {
        switch(opt) {
            case 'p': // Prompt
                prompt = optarg;
                if(prompt == NULL) {
                    print_error("%s: option '-p' requires an argument", program);
                    print_usage(program);
                    return 1;
                }
                break;
            case 'r': // Do not mangle backslashes
                rflag = 1;
                break;
            case 's': // Do not show input (password input style)
                sflag = 1;
                break;
            case '?':
                print_error("%s: invalid option -- '%c'", program);
                print_usage(program);
                return 1;
                break;
        }
    }

    if(prompt != NULL) printf("%s", prompt);

    char buf[1024];
    // TODO implement -r and -s here
    (void)rflag; (void)sflag;
    fgets(buf, 1024, stdin);
    buf[strlen(buf)-1] = '\0'; // strip off '\n' at the end of the buffer

    // do we have a variable to be set as an argument ?
    if(argc > optind) {
        // TODO: fix variable not being set ???
        #ifdef _WIN32
        if(SetEnvironmentVariable(argv[optind], buf) == 0) {
            print_error("%s: setting environment variable '%s' failed", program, argv[optind]);
            return 1;
        }
        #else
        if(setenv(argv[optind], buf, 1) != 0) {
            print_error("%s: setting environment variable '%s' failed", program, argv[optind]);
            return 1;
        }
        #endif // _WIN32

        // double check
        if(getenv(argv[optind]) == NULL) {
            print_error("%s: setting environment variable '%s' failed", program, argv[optind]);
            return 1;
        }
    }
    return 0;
}
