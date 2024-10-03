#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
//#include <unistd.h>

#include "../include/prettyprint.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s -b|-c|-d|-e|-f|-g|-h|-p|-r|-s|-t|-u|-w|-x|-L|-S filename\n", argv0);
  fprintf(stderr, "       %s -z|-n string\n", argv0);
  fprintf(stderr, "       %s value1 comparator value2\n", argv0);
}

int main(int argc, char* argv[]){
  // TODO implement -o, -a, multiple arguments for test
  // TODO implement -eq, -lt, ...
  // Do we use getopt() or do we use our own parser ? (for -eq, -lt, ...)

  int opt;
  char mode = '\0';
  char* test_optarg = NULL;

  // TODO fix print_usage running when not putting an argument for -z and -n
  while((opt = getopt(argc, argv, ":b:c:d:e:f:g:h:p:r:s:t:u:w:x:L:S:z:n:")) != -1) {
    switch(opt) {
      case 'b': // fallthrough
      case 'c': // fallthrough
      case 'd': // fallthrough
      case 'e': // fallthrough
      case 'f': // fallthrough
      case 'g': // fallthrough
      case 'h': // fallthrough
      case 'p': // fallthrough
      case 'r': // fallthrough
      case 's': // fallthrough
      case 't': // fallthrough
      case 'u': // fallthrough
      case 'w': // fallthrough
      case 'x': // fallthrough
      case 'L': // fallthrough
      case 'S': // fallthrough
      case 'z': // fallthrough
      case 'n':
        test_optarg = optarg;
        mode = opt;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  if(argc <= 1 || mode == '\0') {
    print_usage(argv[0]);
    return 1;
  }

  switch(mode) {
    case 'e': // check if file exists
      break;
    case 'z': // check if string length is zero
      if(strlen(test_optarg) == 0) {return 0;}
      else {return 1;}
      break;
    case 'n': // check if string length is non-zero
      if(strlen(test_optarg) != 0) {return 0;}
      else {return 1;}
      break;
  }

  return 0;
}
