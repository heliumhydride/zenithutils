#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../include/prettyprint.h"
#include "../include/util.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [file ...]\n", argv0);
}

int main(int argc, char* argv[]) {
  char ch;

  if (argc < 2) {
    //cat_from_stdin(); // no file arg, read from stdin
    printf("%s", fetch_from_stdin());
  } else {
    for(int fileN=argc-1; fileN > 0; fileN--) {
      if(!strcmp("-", argv[fileN])) {
        //cat_from_stdin();
        printf("%s", fetch_from_stdin());
      } else {
        FILE *fileptr;
        fileptr = fopen(argv[fileN], "r");

        if(NULL==fileptr) {
          print_error("%s: could not open file \"%s\"", argv[0], argv[fileN]);
          return 1;
        }

        // print file contents
        while((ch = fgetc(fileptr)) != EOF) {
          printf("%c", ch);
        }

        // dont forget to close!
        fclose(fileptr);
      }
    }
  }
  return 0;
}
