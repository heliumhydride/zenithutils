#include <stdio.h>           // fprintf(), printf()
#include <stdlib.h>          // strtol()
#include <string.h>          // strcmp()
#include <unistd.h>          // ssize_t
#include "../include/util.h" // print_error()
#include "../config.h"       // FACTOR_MAX_PRIMES

int factor_primes(long n, long* factors, const ssize_t cap)
{
    ssize_t k = 0;

    // Factor out the 2s
    while(n%2 == 0) {
        if(k >= cap) return -1; // not enough space
        factors[k++] = 2;
        n /= 2;
    }

    // Factor out the rest of the primes
    for(long d = 3; d * d <= n; d += 2) {
        while(n%d == 0) {
            if(k >= cap) return -1;
            factors[k++] = d;
            n /= d;
        }
    }

    // Remainder is a prime (>1, because 1 is cheating)
    if(n > 1) {
        if(k >= cap) return -1;
        factors[k++] = n;
    }

    return k;
}

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [numbers...]\n", program);
}

int main(int argc, char* argv[])
{
    const char *program = argv[0];
    shift_args(&argc, &argv);
    if(!strcmp(*argv, "--help")) {
        print_usage(program);
        return 1;
    }

    if(argc < 1) {
        // TODO
        fprintf(stderr, "TODO  coreutils/factor: make use of stdin");
        return 2;
    } else {
        while(*argv) {
            char* endptr;
            long n = strtol(*argv, &endptr, 10);
            if(endptr == *argv || n <= 0) {
                print_error("%s: '%s' is not a positive integer", program, *argv);
                return 1;
            }

            // TODO factor (haha) this out code into some function(s) and use it for stdin too
            long factors[FACTOR_MAX_PRIMES];
            ssize_t count = factor_primes(n, factors, FACTOR_MAX_PRIMES);
            if(count < 0) return 1;

            printf("%ld: ", n);
            for(ssize_t i = 0; i < count; i++)
                printf("%ld%c", factors[i], (i + 1 < count) ? ' ' : '\n');

            shift_args(&argc, &argv);
        }
    }
    return 0;
}
