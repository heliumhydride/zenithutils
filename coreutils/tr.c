#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/prettyprint.h"
#include "../include/util.h"

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [-c] string1 string2\n", program);
    fprintf(stderr, "usage: %s -d [-c] string1\n", program);
}

int main(int argc, char* argv[])
{
    char* string1 = '\0';
    char* string2 = '\0';

    int cflag = 0;
    int dflag = 0;
    int sflag = 0;

    int opt;
    while((opt = getopt(argc, argv, ":cds")) != -1) {
        switch(opt) {
            case 'c': // 'ab' complements 'xy'
                cflag = 1;
                break;
            case 'd': // Delete string1 from stdin. can be used with '-c'
                dflag = 1;
                break;
            case 's': // TODO
                sflag = 1;
                break;
            case '?':
                print_error("%s: invalid option -- '%c'", argv[0], optopt);
                print_usage(argv[0]);
                return 1;
                break;
        }
    }

    if(!dflag && argc <= 2) {
        print_usage(argv[0]);
        return 1;
    }

    string1 = argv[optind];
    if(!dflag) string2 = argv[optind+1];

    if(dflag)
      printf(">> replace %s by nothing\n <<", string1);
    else
      printf(">> replace %s by %s\n <<", string1, string2);

    /* TODO
    if(cflag) {
      // complement
    } else {
      // 'ab' -> 'xy'; 'a' -> 'x'; 'b' -> 'y'
    }
    */

    // TODO no more getbytes_stdin
    printf("%s", getbytes_stdin());
    return 0;
}
