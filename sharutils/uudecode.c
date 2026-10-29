#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [-m] [-p | -o outfile] [encodedfile ...]", program);
}

char* uudecode(char* in)
{
    // TODO: uudecode from 'in' to 'buf'
    // char* buf;
    (void)in;
    return NULL;
}

enum {
    FORMAT_UUENCODE,
    FORMAT_BASE64,
    OUTPUT_NONE,
    OUTPUT_STDOUT,
    OUTPUT_TO_FILE
};

int main(int argc, char* argv[])
{
    int mode = FORMAT_UUENCODE;
    int output = OUTPUT_NONE;

    int opt;
    while((opt = getopt(argc, argv, ":mp:o")) != -1) {
        switch(opt) {
            case 'm':
                mode = FORMAT_BASE64;
                break;
            case 'p':
                output = OUTPUT_STDOUT;
                break;
            case 'o':
                output = OUTPUT_TO_FILE;
                // char* outfilename;
                // TODO get optarg for 'o' to 'outfilename'
                break;
            case '?':
                printf("%s: invalid option -- '%c'", argv[0], optopt);
                print_usage(argv[0]);
                return 1;
                break;
        }
    }

    (void)output;
    // TODO: get inputfile filename (if any, if not use stdin) from argv
    switch(mode) {
      case FORMAT_UUENCODE:
        break;
      case FORMAT_BASE64:
        break;
    }

    return 0;
}
