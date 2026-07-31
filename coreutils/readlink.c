#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
//#include <stdlib.h>
#include <getopt.h>
//#include <string.h>

#include "../include/prettyprint.h"
#include "../config.h"

void print_usage(char* argv0)  {
  fprintf(stderr, "usage: %s [-fevqn] [file] ...\n", argv0);
}

int main(int argc, char* argv[]) {
  int qflag = 0; // Quiet mode -- read link, but do not print filename (exit code only)
  int vflag = 0; // Verbose mode -- prints error messages
  int nflag = 0; // No newline
  int fflag = 0; // Canonicalize paths
  int eflag = 0; // Canonicalize paths; path must exist

  int opt;
  char* program = argv[0];

  while((opt = getopt(argc, argv, ":fevqn")) != -1) {
    switch(opt) {
      case 'f':
        fflag = 1;
        break;
      case 'e':
        fflag = 1;
        eflag = 1;
        break;
      case 'n':
        nflag = 1;
        break;
      case 'v':
        vflag = 1;
        break;
      case 'q':
        qflag = 1;
        break;
      case '?':
        print_error("%s: option error: unknown option '-%c'", program, optopt);
        return 1;
        break;
    }
  }

  // TODO use realpath(...) on Windows
  if(optind == argc) {
    print_usage(program);
    return 1;
  }
  optind--;

  argv += optind;
  if(!argv[0]) { // no non-opt argument is provided
    print_error("%s: path expected", argv[0]);
    print_usage(program);
    return 1;
  }

  // TODO implement -f, -e
  while(*++argv) {
    char buf[MAX_LINK_LENGTH] = {0};
    if(-1 == readlink(*argv, buf, sizeof(buf))) {
      if(vflag) {
        // TODO error handling
        print_error("%s: '%s': invalid argument", program, *argv);
      }
      return 1;
    } else {
      if(!qflag) {
        printf("%s", buf);
        if(!nflag) // TODO ignore -n when multiple arguments are provided
          printf("\n");
      }

    }
  }
  return 0;
}

