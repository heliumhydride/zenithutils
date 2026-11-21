#define _XOPEN_SOURCE 500    // usleep()
#include <stdio.h>           // fprintf(), printf()
#include <stdlib.h>          // strtol()
#include <unistd.h>          // usleep() [_XOPEN_SOURCE>=500]
#include "../include/util.h" // print_error()

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [microseconds]\n", program);
}

int main(int argc, char* argv[])
{
    const char *program = argv[0]
    shift_args(&argc, &argv);

    if(argc <= 0) {
        print_usage(program);
        return 1;
    }

    char *endptr;
    long t = strtol(*argv, &endptr, 10);
    if(endptr == *argv) {
        print_error("%s: '%s' is not a number", program, *argv);
        return 1;
    }

    usleep(t);
    return 0;
}
