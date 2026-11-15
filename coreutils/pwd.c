#define _POSIX_C_SOURCE 200809L // PATH_MAX
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/util.h"
#include "../config.h"

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif // !PATH_MAX

void print_usage(char* program)
{
    fprintf(stderr, "usage: %s [-LP]", program);
}

int main(int argc, char* argv[])
{
    char cwd[PATH_MAX];

    int Lflag = 0;
    int opt;
    while((opt = getopt(argc, argv, ":LP")) != -1) {
        switch(opt) {
            case 'L': // Use the PWD variable on unix and the CD variable on Windows (logical working directory)
                Lflag = 1;
                break;
            case 'P': // Resolve symlinks (aka. "Print physical working directory")
                break;
            case '?':
                print_error("%s: invalid option -- '%c'", argv[0], optopt);
                print_usage(argv[0]);
                return 1;
                break;
        }
    }

    if(!Lflag) { // We use OS functions (normal pwd behaviour)
        #ifdef _WIN32
        GetCurrentDirectory(PATH_MAX, cwd);
        if(FORCE_MINGW_PATHS) {
            char* m_cwd = malloc(strlen(cwd));
            mingw_path(m_cwd, cwd);
            printf("%s\n", m_cwd);
        } else {
            printf("%s\n", cwd);
        }
        #else // On Unix
        if(getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            print_error("%s: getcwd() failed", argv[0]);
            return 1;
        }
        #endif // _WIN32
    } else { // We use PWD/CD environment variable (gnu pwd -L behaviour)
        if(getenv("PWD") != NULL) {
            printf("%s\n", getenv("PWD"));
        } else {
            // TODO: returns null on wine ? To be tested on real Windows
            printf("%s\n", getenv("CD"));
        }
    }

    return 0;
}
