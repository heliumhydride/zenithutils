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

  // TODO: implement cat -belnstuv parameters w/ while getopt (see chimerautils cat)
  //print_usage(argv[0]);

  if (argc < 2) {
    //getbytes_stdin(); // no file arg, read from stdin
    printf("%s", getbytes_stdin());
  } else {
    for(int fileN=1; fileN < argc; fileN++) {
      if(!strcmp("-", argv[fileN])) {
        printf("%s", getbytes_stdin());
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
          // TODO: implement -v / -e for displaying TAB and NEWLINES as other chars
        }

        // dont forget to close!
        fclose(fileptr);
      }
    }
  }
  return 0;
}
