#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <dirent.h>
#include "../include/prettyprint.h"
#include "../include/util.h"

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
    const char* program = argv[0];
    int opt;
    int pflag = 0; // create directories recursively
    int vflag = 0; // show operations / verbose mode
    int mflag = 0; // using mode flag to set mode
    mode_t mode = 0755;
    #if !defined(_WIN32) // On Unix
    mode_t process_umask = 0;
    #endif // !_WIN32

    while((opt = getopt(argc, argv, ":m:pv")) != -1) {
      switch(opt) {
          case 'v':
              vflag = 1;
              break;
          case 'p':
              pflag = 1;
              break;
          case 'm':
              mflag = 1;
              if(!is_mode_t(optarg)) {
                print_error("%s: invalid mode '%s'", optarg);
                return 1;
              }
              mode = (mode_t)strtol(optarg, NULL, 8);
              #if defined(_WIN32) // On Unix
              process_umask = umask(0);
              #endif // !_WIN32
              break;
          case '?': // fallthrough
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

    (void)vflag; // TODO
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
        }
    }

    #if !defined(_WIN32) // On Unix
    if(mflag) (void)umask(process_umask);
    #endif // !_WIN32

    return excode;
}
