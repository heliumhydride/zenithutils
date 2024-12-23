#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

#include "../include/prettyprint.h"
#include "../include/util.h"

void nonprint_alt(char* buf, char c) {
  // Give a two character alternative to a non-printable character
  /* N.B: if you put all non printable chars from NULL(0x00) to US(0x1F)
    you can see that cat prints out ^@^A...
    And in the ascii table, @ = 64, A = 65...
    And 0 is mapped to 64, 1 to 65, ...
    So we can deduce a pattern here, it is that we
    print '^' and then (c+64)
  */
  
  buf[0] = '^';
  buf[1] = c+64; // see note
  buf[2] = '\0'; // null-terminate string
}

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-beElnstuv] [file ...]\n", argv0);
}

int main(int argc, char* argv[]) {
  // TODO implement cat -v, -n and -E
  int opt;
  int vflag,Eflag,nflag;
  vflag = Eflag = nflag = 0;
  char* program = argv[0];

  while((opt = getopt(argc, argv, ":veEn")) != -1) {
    switch(opt) {
      case 'v': // Show non-printing
        vflag = 1;
        break;
      case 'E': // Show end of lines '$'
        Eflag = 1;
        break;
      case 'e': // equivalent to -vE
        vflag = Eflag = 1;
        break;
      case 'n':
        nflag = 1;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", program, optopt);
        print_usage(program);
        return 1;
        break;
    }
  }
  optind--;

  argv += optind;
  if(!argv[0]) {
    print_usage(program);
  }

  ssize_t filesize;
  FILE* fileptr;
  size_t line_counter = 1;
  char* minibuf = malloc(3);

  while(*++argv) {
    if(argc == optind) { // Read from stdin if no argument other than opts is provided
      filesize = STDIN_MAX;
      fileptr = stdin;
    } else { // We read from file
      fileptr = fopen(*argv, "r");
      filesize = get_filesize(fileptr);
      if(NULL == fileptr) {
        print_error("%s: could not open file \"%s\"", program, *argv);
        return 1;
      }
    }
  
    char* line = malloc(filesize);
    while((line = fgets(line, filesize, fileptr)) != NULL) {
      line[strlen(line)-1] = '\0'; // strip '\n' off the string
      if(nflag)
        printf("%6zu  ", line_counter);
      for(size_t i = 0; i <= strlen(line); i++) {
        if(vflag && !is_printable_ch(line[i])) {
          // TODO wrong cat output for test file with all non-print characters
          // eg. with -vE, I get ^@$ instead of just $ sometimes
          nonprint_alt(minibuf, line[i]);
          printf("%s", minibuf);
        } else {
          printf("%c", line[i]);
        }
      }
      if(Eflag)
        printf("$");
      printf("\n");
      line_counter++;
    }
    fclose(fileptr);
    free(line);
  }

  free(minibuf);
  return 0;
}
