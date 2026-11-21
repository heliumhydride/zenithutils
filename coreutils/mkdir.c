#define _XOPEN_SOURCE 500     // strdup()
#include <stdio.h>            // fprintf(), printf(), snprintf()
#include <stdlib.h>           // strtol(), free()
#include <sys/stat.h>         // stat(), S_ISDIR()
#include <getopt.h>           // getopt(), optind, optopt, optarg
#include <string.h>           // strcmp(), strdup()
#include <errno.h>            // errno, EINVAL, EEXIST, ENOTDIR
#include <libgen.h>           // dirname()
#include "../include/util.h"  // mkdir2(), is_mode_t(), print_error(), perror2()

char *program;
static int vflag = 0;

int direxists(const char* pathname)
{
    struct stat st;
    if(stat(pathname, &st) != 0) return 0;
    return S_ISDIR(st.st_mode);
}

int mkdir_p(const char* pathname, mode_t mode)
{
    if(pathname == NULL) {
        errno = EINVAL;
        return -1;
    }

    if(!strcmp(pathname, "/") || !strcmp(pathname, ".") || !strcmp(pathname, ".."))
        return 0;

    char* tmp = strdup(pathname); // because on glibc dirname can modify pathname?
    if(tmp == NULL) return -1;

    char* parent = dirname(tmp);
    if(!direxists(parent))
        mkdir_p(parent, mode);

    if(mkdir2(pathname, mode) == 0) {
        if(vflag)
            printf("%s: created directory '%s'\n", program, pathname);
        free(tmp);
        return 0;
    }

    if(errno == EEXIST) {
        if(direxists(pathname)) {
            free(tmp);
            return 0;
        } else {
            errno = ENOTDIR;
            free(tmp);
            return -1;
        }
    }

    free(tmp);
    return -1;
}

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [-m mode] [-pv] dir [dir] ...\n", program);
}

int main(int argc, char* argv[])
{
    program = argv[0];

    int opt;
    int pflag = 0; // create directories recursively
    // int vflag = 0; // show operations / verbose mode

    mode_t mode = 0755;
    #if !defined(_WIN32) // On Unix
    mode_t process_umask = umask(0);
    #endif // !_WIN32

    while((opt = getopt(argc, argv, ":m:pv")) != -1) {
        switch(opt) {
            char *old_optarg;
            case 'v':
                vflag = 1;
                break;
            case 'p':
                pflag = 1;
                break;
            case 'm':
                old_optarg = optarg;
                if(!is_mode_t(optarg)) {
                  print_error("%s: invalid mode '%s'", program, old_optarg);
                  return 1;
                }
                mode = (mode_t)strtol(optarg, NULL, 8);
                break;
            case '?':
                print_error("%s: option error: unknown option '-%c'", program, optopt);
                print_usage(program);
                return 1;
                break;
            case ':':
                print_error("%s: option '-%c' needs an argument", program, optopt);
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

    int excode = 0;
    while(*++argv) {
        int status;
        if(pflag) status = mkdir_p(*argv, mode);
        else      status = mkdir2(*argv, mode);

        if(status == -1) {
            char errstring[150] = {0};
            snprintf(errstring, sizeof(errstring), "creating directory '%s' failed", *argv);
            perror2(errstring, program);
            excode = 1;
            break;
        } else {
            if(!pflag && vflag)
                printf("%s: created directory '%s'\n", program, *argv);
        }
    }

    #if !defined(_WIN32) // On Unix
    umask(process_umask);
    #endif // !_WIN32

    return excode;
}
