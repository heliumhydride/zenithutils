#include <stdio.h>            // fprintf(), printf()
#include <stdlib.h>           // strtol()
#include <string.h>           // strcmp()
#include <sodium.h>           // sodium_init(), randombytes_uniform()
#include "../include/util.h"  // print_error(), str_is_nan(), shift_args()

void print_usage(const char *program)
{
    fprintf(stderr, "usage: %s [min] max\n", program);
}

int main(int argc, char *argv[])
{
    const char *program = argv[0];
    shift_args(&argc, &argv);
    long min = 0;
    long max = 0;

    if(sodium_init() == -1) {
        print_error("%s: sodium_init() failed", program);
        return 1;
    } 

    if(argc <= 0 || strcmp("--help", *argv) == 0) {
        print_usage(program);
        return 1;
    }
    
    char *endptr;
    if(argc == 1) { // We have one arg
        max = strtol(*argv, &endptr, 10);
        if(endptr == *argv) {
            print_error("%s: '%s' is not a valid long integer", program, *argv);
            return 1;
        }
    } else if(argc >= 2) {
        min = strtol(*argv, &endptr, 10);
        if(endptr == *argv) {
            print_error("%s: '%s' is not a valid long integer", program, *argv);
            return 1;
        }

        shift_args(&argc, &argv);
        max = strtol(*argv, &endptr, 10);
        if(endptr == *argv) {
            print_error("%s: '%s' is not a valid long integer", program, *argv);
            return 1;
        }
    }
    
    printf("%ld\n", (long)(randombytes_uniform(max-min) + min));
    return 0;
}
