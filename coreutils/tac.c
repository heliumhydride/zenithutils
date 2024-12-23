#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
#include <stdlib.h>
//#include <getopt.h>
#include <unistd.h>
#include <string.h>

#include "../include/prettyprint.h"
#include "../include/util.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [file ...]\n", argv0);
}

int main(int argc, char* argv[]) {
  ssize_t filesize;
  FILE* fileptr;
  char* program = argv[0];

  while(*++argv) {
    if(argc <= 1) {
      fileptr = stdin;
      filesize = STDIN_MAX;
    } else {
      fileptr = fopen(*argv, "r");
      if(NULL == fileptr) {
        print_error("%s: could not open file \"%s\"", program, *argv);
        return 1;
      }
      filesize = get_filesize(fileptr);
    }
    // TODO get amount of lines in file (by using readfile to get each bytes) and take function size_t count_lines(const char* str) from coreutils/wc.c, make an array of char* with the size of the number of lines in the buffer and store each line in reverse from the buffer, then print this array
    char* line = malloc(filesize);
    while((line = fgets(line, filesize, fileptr)) != NULL) {
      line[strlen(line)-1] = '\0'; // strip '\n' off the line
      for(size_t i = 0; i <= strlen(line); i++)
        printf("%c", line[i]);
      printf("\n");
    }
    fclose(fileptr);
    free(line);
  }
  return 0;
}
