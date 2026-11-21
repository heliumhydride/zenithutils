#include <stdio.h>           // fprintf(), printf(), snprintf(), fseek(), fopen(), fclose(), fgetc(), fputc(), SEEK_*
#include <stdlib.h>          // strtol()
#include <getopt.h>          // getopt(), optind, optopt, optarg
#include <sodium.h>          // sodium_init(), randombytes_random()
#include <unistd.h>          // unlink()
#include "../include/util.h" // print_error(), perror2()

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [-n iterations] [-u] file\n", program);
}

int main(int argc, char* argv[])
{
    const char* program = argv[0];

    if(sodium_init() < 0) {
        print_error("%s: libsodium sodium_init() failed", program);
        return 1;
    }

    long n_iterations = 3;
    int uflag = 0;
    int opt;
    char* endptr = NULL;
    while((opt = getopt(argc, argv, ":n:u")) != -1) {
        switch(opt) {
            case 'n':
                n_iterations = strtol(optarg, &endptr, 10);
                if(optarg == endptr) {
                    print_error("%s: %s is not a positive integer", program, optarg);
                    return 1;
                }
                break;
            case 'u':
                uflag = 1;
                break;
            case '?':
                print_error("%s: option error: unknown option '-%c'", program, optopt);
                print_usage(program);
                return 1;
                break;
            case ':':
                print_error("%s: option '-%c' requires an argument", program, optopt);
                print_usage(program);
                return 1;
                break;
        }
    }

    argc -= optind;
    argv += optind;
    if(argc == 0) {
        print_usage(program);
        return 1;
    }

    FILE* fp = fopen(*argv, "r+");
    if(fp == NULL) {
        char errstring[150] = {0};
        snprintf(errstring, sizeof(errstring), "could not open file %s", *argv);
        perror2(errstring, program);
        return 1;
    }

    for(long i = 0; i < n_iterations; i++) {
        int c;
        while((c = fgetc(fp)) != EOF) {
            fseek(fp, -1L, SEEK_CUR); // we just fgetc, which goes forward 1 character, so go back to write over it
            fputc(randombytes_random(), fp);
        }
        fseek(fp, 0L, SEEK_SET);
    }

    fclose(fp);
    if(uflag) {
        if(unlink(*argv) == -1) {
            char errstring[150] = {0};
            snprintf(errstring, sizeof(errstring), "'%s': could not remove file", *argv);
            perror2(errstring, program);
            return 1;
        }
    }
    return 0;
}
