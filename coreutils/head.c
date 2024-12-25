#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
//#include <string.h>

#include "../include/prettyprint.h"
#include "../include/util.h"
#include "../config.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-n int] [-v|-q]\n", argv0);
}

int main(int argc, char* argv[]) {
  int opt;
  long n_lines = 10; // default: -n10
  int verbosity = 1; // quiet:0 normal:1 full:2
  char* program = argv[0];

  // If -q is used in conjuction with -v, -v takes the upper hand. (that's what you get for using both options!)
  while((opt = getopt(argc, argv, ":n:qv")) != -1) {
    switch(opt) {
      case 'n':
        if(str_is_nan(optarg)) {
          print_error("%s: invalid integer '%s'", program, optarg);
        }
        n_lines = atol(optarg);
        break;
      case 'q':
        verbosity = 0;
        break;
      case 'v':
        verbosity = 2;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", program, optopt);
        print_usage(program);
        return 1;
        break;
      case ':':
        print_error("%s: option '%c' needs an argument", program, optopt);
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
  char* line;
  size_t line_counter;

  while(*++argv) {
    if((argc == optind) || (*argv == "-")) { // Read from stdin if no argument other than opts are provided / file is -
      filesize = STDIN_MAX;
      fileptr = stdin;
      if(verbosity >= 2)
        printf("==> standard input <==\n");
    } else { // We read from a file
      fileptr = fopen(*argv, "r");
      if(NULL == fileptr) {
        print_error("%s: could not open file \"%s\"", program, *argv);
        return 1;
      }
      filesize = get_filesize(fileptr);
    }

    line = malloc(filesize);
    line_counter = 1;
    if((verbosity >= 2) && (fileptr != stdin))
      printf("==> %s <==\n", *argv);
    while(((line = fgets(line, filesize, fileptr)) != NULL) && (line_counter <= n_lines)) {
      line[strlen(line)-1] = '\0'; // strip '\n' off the string
      for(size_t i = 0; i <= strlen(line); i++) {
        printf("%c", line[i]);
      }
      printf("\n");
      line_counter++;
    }
    fclose(fileptr);
    free(line);
  }
  return 0;
}
