#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sodium.h>
#include "../include/prettyprint.h"
#include "../include/util.h"

const char* charset = "0123456789abcdef";

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [-C num] | [-h]\n", program);
}

void uuidgen(char* uuid)
{
    for(int i = 0; i < 36; i++)
        uuid[i] = charset[randombytes_uniform(16)];

    // Add the separators
    uuid[8] = uuid[13] = uuid[18] = uuid[23] = '-';
    uuid[36] = '\0'; // null terminate also
}

int main(int argc, char* argv[])
{
    if(sodium_init() < 0) {
        print_error("%s: libsodium sodium_init failed", argv[0]);
        return 1;
    }

    size_t count = 1;
    int opt;
    while((opt = getopt(argc, argv, ":C:h")) != -1) {
        switch(opt) {
            case 'C':
                if(str_is_nan(optarg) || atol(optarg) <= 0) {
                    print_error("%s: '%s' is not a positive number", argv[0], optarg);
                    return 1;
                }
                count = atol(optarg);
                break;
            case '?':
                print_error("%s: invalid option -- '%c'", argv[0], optopt);
                // fallthrough
            case 'h':
                print_usage(argv[0]);
                return 1;
                break;
        }
    }
    
    // cool tip: when you can avoid malloc avoid it please
    // especially when you want to allocate a fixed amount of memory...
    char u[37] = {0};
    for(size_t i = 0; i < count; i++) {
        uuidgen(u);
        puts(u);
    }

    return 0;
}
