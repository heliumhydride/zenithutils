#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <inttypes.h>

#include "../include/prettyprint.h"
#include "../include/util.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [first [increment]] last\n", argv0);
}

int main(int argc, char* argv[]) {
  ssize_t last;
  ssize_t first = 1;
  ssize_t increment = 1;
  char separator = '\n'; // default separator to newline

  if(argc < 2) {
    print_usage(argv[0]);
    return 1;
  }

  if(str_is_nan(argv[1])) {
    print_error("%s: '%s' is not a number", argv[0], argv[1]);
    return 1;
  }

  last = (ssize_t)strtoimax(argv[1], NULL, 10);

  if(argc == 3) {
    if(str_is_nan(argv[1]) || str_is_nan(argv[2])) {
      print_error("%s: an input is not a number", argv[0]);
      return 1;
    }

    first = (ssize_t)strtoimax(argv[1], NULL, 10);
    last = (ssize_t)strtoimax(argv[2], NULL, 10);
  }

  if(argc == 4) {
    if(str_is_nan(argv[1]) || str_is_nan(argv[2]) || str_is_nan(argv[3])) {
      print_error("%s: an input is not a number", argv[0]);
      return 1;
    }

    first = (ssize_t)strtoimax(argv[1], NULL, 10);
    increment = (ssize_t)strtoimax(argv[2], NULL, 10);
    last = (ssize_t)strtoimax(argv[3], NULL, 10);
  }

  if(argc > 4) {
    print_error("%s: too many arguments", argv[0]);
    return 1;
  }

  if(increment == 0) {
    print_error("%s: increment cannot equal zero", argv[0]);
    return 1;
  }

  if(increment >= 1) {
    for(ssize_t i = first; i <= last; i += increment)
      printf("%zd%c", i, separator);
  } else {
    for(ssize_t i = first; i >= last; i += increment)
      printf("%zd%c", i, separator);
  }

  return 0;
}
