#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
//#include <stdlib.h>
//#include <string.h>

#include "../include/prettyprint.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-cdu] [infile [outfile]]", argv0);
}

int main(int argc, char* argv[]){
  int opt;
  int cflag = 0;
  int dflag = 0;
  int uflag = 0;

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

  char* stdin_buffer;

  if(argc == optind) { // No arg, we read from stdin
    // TODO fix segfault after stdin read
    stdin_buffer = fetch_from_stdin();
    if(NULL == stdin_buffer) {
      print_error("%s: fetch_from_stdin() failed", argv[0]);
      return 1;
    }
  } else { // We read from a file
    FILE* fileptr;
    fileptr = fopen(argv[optind], "r");
    if(NULL == fileptr) {
      print_error("%s: could not open file \"%s\"", argv[0], argv[optind]);
      return 1;
    }

    char ch;
    if(fseek(fileptr, 0L, SEEK_END) == 0) {
      size_t filesize = ftell(fileptr);
      if(filesize == -1) {
        print_error("%s: ftell() failed", argv[0]);
        return 1;
      }

      stdin_buffer = malloc(sizeof(char) * (filesize + 1));

      if(fseek(fileptr, 0L, SEEK_SET) != 0) {
        print_error("%s: fseek() failed", argv[0]);
        return 1;
      }

      size_t newlen = fread(stdin_buffer, sizeof(char), filesize, fileptr);
      if(ferror(fileptr) != 0) {
        print_error("%s: reading file \"%s\" failed", argv[0], argv[optind]);
      } else {
        stdin_buffer[newlen++] = '\0';
      }
    }
    fclose(fileptr);
  }

  printf("%s", stdin_buffer);
  // TODO split into each line
  // TODO go through each line and either show only duplicates or unique lines (store previous file into prev_linebuffer)

	return 0;
}
