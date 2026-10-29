#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/prettyprint.h"
#include "../include/util.h"

void print_usage(const char* program)
{
  fprintf(stderr, "usage: %s [-cdu] [infile [outfile]]", program);
}

int main(int argc, char* argv[])
{
    int cflag = 0;
    int dflag = 0;
    int uflag = 0;

    int opt;
    while((opt = getopt(argc, argv, ":cdu")) != -1) {
        switch(opt) {
          case 'c':
              cflag = 1;
              break;
          case 'd':
              dflag = 1;
              break;
          case 'u':
              uflag = 1;
              break;
          case '?':
              print_error("%s: invalid option -- '%c'", argv[0], optopt);
              print_usage(argv[0]);
              return 1;
              break;
        }
    }
    // TODO allow taking one or two file args, while still keeping getopt working correctly (see usage, infile, outfile)

    char* stdin_buffer;
    char* old_line;
    char* current_line;
    int count = 1; // TODO count occurences of a line

    // TODO no more getbytes_stdin, rework all of this in general
    if(argc == optind) { // No arg, we read from stdin
        stdin_buffer = getbytes_stdin();
        if(NULL == stdin_buffer) {
            print_error("%s: getbytes_stdin() failed", argv[0]);
            return 1;
        }
    } else { // We read from a file
        FILE* fileptr = fopen(argv[optind], "r");
        if(NULL == fileptr) {
            print_error("%s: could not open file \"%s\"", argv[0], argv[optind]);
            return 1;
        }

        stdin_buffer = malloc(get_filesize(fileptr)+1);
        if(readfile(fileptr, input_buffer) == -1)
            print_error("%s: read error", argv[0]);
        fclose(fileptr)
    }

    // TODO split into each line (see tac.c for example)
    while((current_line = strsep(&stdin_buffer, "  ")) != NULL) {
      if(cflag == 1)
          printf("%8d ", count);
      if(uflag != 1 && current_line != old_line)
          printf("%s\n", current_line);
      old_line = current_line;
    }
    // TODO go through each line and either show only duplicates or unique lines (store previous file into prev_linebuffer)

    return 0;
}
