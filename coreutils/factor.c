#include <stdio.h>           // fprintf(), printf()
#include <stdlib.h>          // strtol()
#include <string.h>          // strcmp(), strlen()
#include <unistd.h>          // ssize_t
#include "../include/util.h" // print_error()
#include "../config.h"       // FACTOR_MAX_PRIMES, STDIN_MAX

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

int print_factors(long n)
{
    // on error, 1 is returned
    long factors[FACTOR_MAX_PRIMES];
    ssize_t count = factor_primes(n, factors, FACTOR_MAX_PRIMES);
    if(count < 0) return 1;

    printf("%ld: ", n);
    for(ssize_t i = 0; i < count; i++)
        printf("%ld%c", factors[i], (i + 1 < count) ? ' ' : '\n');
    return 0;
}

int main(int argc, char* argv[])
{
    const char *program = argv[0];
    shift_args(&argc, &argv);

    if(argc >= 1 && !strcmp(*argv, "--help")) {
        print_usage(program);
        return 1;
    }

    long n;
    char *endptr;
    int excode = 0;
    if(argc <= 0) {
        for(;;) {
            char buf[STDIN_MAX];
            if(fgets(buf, STDIN_MAX, stdin) == NULL) {
                print_error("%s: reading from stdin failed", program);
                return 2;
            }

            n = strtol(buf, &endptr, 10);
            if(endptr == buf || n <= 0) {
                // strip newline before printing error
                buf[strlen(buf) - 1] = '\0';
                print_error("%s: '%s' is not a valid positive integer", program, buf);
                excode = 1;
                continue;
            }
            if(print_factors(n))  return 1;
        }
    } else {
        while(*argv) {
            n = strtol(*argv, &endptr, 10);
            if(endptr == *argv || n <= 0) {
                print_error("%s: '%s' is not a valid positive integer", program, *argv);
                excode = 1;
                shift_args(&argc, &argv);
                continue;
            }

            if(print_factors(n))  return 1;
            shift_args(&argc, &argv);
        }
    }
    return excode;
}
