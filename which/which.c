#define _POSIX_C_SOURCE 200809L
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/util.h"

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif // !PATH_MAX

// all of the variables below need to be defined globally for is_there() and print_matches() to access
static int sflag;
static int aflag;

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [-as] program ...\n", program);
}

int is_there(char* candidate)
{
    char* new_candidate;

    #if defined(_WIN32) && FORCE_MINGW_PATHS
    new_candidate = malloc(strlen(candidate) + 1);
    mingw_path(new_candidate, candidate);
    #else
    new_candidate = candidate;
    #endif // _WIN32, FORCE_MINGW_PATHS

    if(!access(candidate, X_OK)) {
        if(!sflag) puts(new_candidate);
        return 1;
    }

    return 0;
}

int print_matches(char* path, char* filename)
{
    char candidate[PATH_MAX];
    const char* d;

    if(strchr(filename, '/') != NULL)
        return is_there(filename) - 1;
        // return (is_there(filename) ? 0 : -1);

    int found = 0;
    // TODO: if compiling for Windows, accept both ':' and ';' as separator, but not mixed
    // TODO: check in current directory on Windows
    #ifdef _WIN32
    char* path_env_sep = ";";
    #else // On Unix
    char* path_env_sep = ":";
    #endif
    while((d = strsep(&path, path_env_sep)) != NULL) {
        if (*d == '\0') d = ".";
        char dir_sep = '/';
        #if defined(_WIN32) // && !FORCE_MINGW_PATHS
        dir_sep = '\\';
        #endif // _WIN32

        if(snprintf(candidate, sizeof(candidate), "%s%c%s", d, dir_sep, filename) >= (int)sizeof(candidate)) continue;

        if(is_there(candidate)) {
            found = 1;
            if(!aflag) break;
        } else {
            // try again but append .exe (so we can call 'which cmd' for example)
            strcat(candidate, ".exe");
            if(is_there(candidate)) {
                found = 1;
                if(!aflag) break;
            }
        }
    }

    return found - 1;
    // return (found ? 0 : -1);
}

int main(int argc, char* argv[])
{
    sflag = 0;
    aflag = 0;

    int opt;
    while((opt = getopt(argc, argv, ":as")) != -1) {
        switch(opt) {
            case 'a': // enable all paths, not just the first one
                aflag = 1;
                break;
            case 's': // silent which (no output, only exit code)
                sflag = 1;
                break;
            case '?':
                print_error("%s: invalid option -- '%c'", argv[0], optopt);
                print_usage(argv[0]);
                return 1;
                break;
        }
    }


    if(argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    char* p;
    if((p = getenv("PATH")) == NULL)
        p = "";

    size_t pathlen = strlen(p) + 1;
    char path[pathlen];

    //int optind_orig = optind; // just in case for future use
    for(; optind < argc; optind++) {
        memcpy(path, p, pathlen);
        if(print_matches(path, argv[optind]) == -1)
            fprintf(stderr, "%s: no %s in (%s)", argv[0], argv[optind], p);
        // TODO return 2 if at least one of the programs were not found
    }

    return 0;
}
