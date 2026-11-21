#include <stdio.h>            // fprintf(), puts()
#include <getopt.h>           // getopt(), optind
#include <string.h>           // strlen()
#include "../include/util.h"  // print_error()
#include "../config.h"        // STDIN_MAX

static int pflag = 0; // {mingw,win32}path2 need to know about this

void mingw_path2(char* path)
{
    for(size_t i = 0; i < strlen(path); i++) {
        if(path[i] == '\\')          path[i] = '/';
        if(pflag && path[i] == ';')  path[i] = ':';
    }
}

void win32_path2(char* path)
{
    for(size_t i = 0; i < strlen(path); i++) {
        if(path[i] == '/')           path[i] = '\\';
        if(pflag && path[i] == ':')  path[i] = ';';
    }
}

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [-mw] [path]\n", program);
}

int main(int argc, char* argv[])
{
    const char* program = argv[0];

    char mode = 'm';
    int opt;
    while((opt = getopt(argc, argv, ":mwp")) != -1) {
        switch(opt) {
            case 'w':
                mode = 'w';
                break;
            case 'p':
                pflag = 1;
                break;
            case '?':
                print_error("%s: option error: unknown option '-%c'", program, optopt);
                print_usage(program);
                return 1;
                break;
        }
    }

    argc -= optind;
    argv += optind - 1;

    if(argc == 0) {
        char buf[STDIN_MAX];
        int c;
        size_t i = 0;
        while((c = getchar()) != EOF) {
            buf[i] = (char)c;
            i++;
        }

        switch(mode) {
            case 'm':
                mingw_path2(buf);
                break;
            case 'w':
                win32_path2(buf);
                break;
        }
        puts(buf);
    } else {
        while(*++argv) {
            switch(mode) {
                case 'm':
                    mingw_path2(*argv);
                    break;
                case 'w':
                    win32_path2(*argv);
                    break;
            }
            puts(*argv);
        }
    }

    return 0;
}
