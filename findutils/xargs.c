#define  _XOPEN_SOURCE 500    // strdup()
#include <stdio.h>            // fprintf(), getchar()
#include <string.h>           // strtok(), strdup()
#include "../include/util.h"  // cmd_t, cmd_run(), da_append(), da_destroy(), print_error()
#include "../config.h"        // STDIN_MAX

// TODO -0 option
void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s command [initial args]\n", program);
}

int main(int argc, char* argv[])
{
    const char* program = argv[0];
    shift_args(&argc, &argv);

    if(argc == 0) {
        print_usage(program);
        return 1;
    }

    if(argc >= 1 && !strcmp(*argv, "--help")) {
        print_usage(program);
        return 0;
    }

    char* path = *argv;
    char buf[STDIN_MAX] = {0};
    int c;
    int i = 0;
    while((c = getchar()) != EOF) {
        buf[i] = (char)c;
        i++;
    }
    buf[i] = '\0';

    // start building new argv from the program's one (after the program path)
    cmd_t cmd = {0};
    da_append(&cmd, path);
    while(*++argv) da_append(&cmd, *argv);

    // build the rest of new argv from buffer (stdin)
    const char* separators = " \n\t";
    char* pch = strtok(buf, separators);
    while(pch != NULL) {
        da_append(&cmd, strdup(pch));
        pch = strtok(NULL, separators);
    }

    int res = cmd_run(&cmd);
    da_destroy(&cmd);
    return res;
}

