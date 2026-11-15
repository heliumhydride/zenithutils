#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
//#include <getopt.h>
#include "../include/util.h" // includes "../include/color.h"
#include "../config.h"

#define DT_UNKNOWN 0
#define DT_FIFO 1
#define DT_CHR 2
#define DT_DIR 4
#define DT_BLK 6
#define DT_REG 8
#define DT_LNK 10
#define DT_SOCK 12
#define DT_WHT 14

// TODO print individual files with color
// TODO separate filename printing function
// TODO show directory names if there are multiple directories
// TODO options
// TODO formatting

int main(int argc, char* argv[])
{
    const char* program = argv[0];
    char type = 'd';

    if(argc < 2) {
        argv--;
        argv[1] = ".";
    }

    DIR* d;
    struct dirent* ent;
    while(*++argv) {
        // Try to open whatever path we got before us, be it a directory or a file
        d = opendir(*argv);
        switch(errno) {
            case ENOTDIR:
              type = 'f';
              break;
            case EACCES:
              print_error("%s: '%s': Access denied", program, *argv);
              return 1;
              break;
            case ENOENT:
              print_error("%s: '%s': No such file or directory", program, *argv);
              return 1;
              break;
        }

        switch(type) {
            case 'd':
                while((ent = readdir(d))) {
                    #if LS_COLOR && !defined(_WIN32) // TODO d_type not supported on mingw?
                    switch(ent->d_type) {
                        case DT_BLK: // fallthrough
                        case DT_CHR: // bright yellow
                            printf(ANSI_YELLOW);
                            break;
                        case DT_DIR:
                            printf(ANSI_BLUE);
                            break;
                        case DT_FIFO:
                        case DT_SOCK:
                            printf(ANSI_MAGENTA);
                            break;
                        case DT_LNK:
                            printf(ANSI_CYAN);
                            break;
                        default: // any other file, check executable permission
                            #ifdef _WIN32
                            if(
                              file_ext_is(ent->d_name, "exe") ||
                              file_ext_is(ent->d_name, "cmd") ||
                              file_ext_is(ent->d_name, "bat")
                            ) // TODO this configuration is not hardcoded into windows
                            #else // On Unix
                            if(access(ent->d_name, X_OK) == 0)
                            #endif
                              printf(ANSI_GREEN);
                            break;
                    }
                    #endif // LS_COLOR, !_WIN32

                    printf("%s ", ent->d_name);

                    #if LS_COLOR && !defined(_WIN32)
                    printf(ANSI_NORM);
                    #endif // LS_COLOR, !_WIN32
                }
                break;
            case 'f':
                printf("%s ", *argv);
                break;
        }
        if(type == 'd') closedir(d);
        putchar('\n');
    }

    return 0;
}
