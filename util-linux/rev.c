#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
#include <stdlib.h>
//#include <getopt.h>
//#include <unistd.h>
#include <string.h>

#include "../include/prettyprint.h"

int main(int argc, char* argv[]) {
  int use_stdin = 0;
  if(argc <= 1) {
    use_stdin = 1;
  }

  FILE* fileptr;
  if(use_stdin) {
    fileptr = stdin;
  } else {
    fileptr = fopen(argv[1], "r");
  }

  // get filesize here
  size_t filesize;
  if(use_stdin) {
    filesize = 4096; // today i realized nobody puts more than 4096 characters into stdin, tested with rev from util-linux
  } else {
    if(fseek(fileptr, 0L, SEEK_END) != 0) {
      print_error("%s: fseek() failed", argv[0]);
      return 2;
    }
    if((filesize = ftell(fileptr)) == -1) {
      print_error("%s: ftell() failed", argv[0]);
      return 2;
    }
    if(fseek(fileptr, 0L, SEEK_SET) != 0) {
      print_error("%s: fseek() failed", argv[0]);
      return 2;
    }
  }

  char* line = malloc(filesize);
  while((line = fgets(line, filesize, fileptr)) != NULL) {
    line[strlen(line)-1] = '\0'; // strip '\n' off the string
    for(int i = strlen(line)-1; i >= 0; i--) { // print each character of the line, from last to first
      printf("%c", line[i]);
    }
    printf("\n"); // print newline at the end still
  }
  return 0;
}
