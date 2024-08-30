#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#include "../include/prettyprint.h"
#include "../include/util.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s first [increment] [last]\n", argv0);
}

int main(int argc, char* argv[]){
  ssize_t first;
  size_t last;
  ssize_t increment;

  if(argc < 2) {
    print_usage(argv[0]);
    return 1;
  }

  if(str_is_nan(argv[1])) {
    print_error("%s: '%s' is not a number", argv[0], argv[1]);
    return 1;
  }

  last = atol(argv[1]);
  increment = 1;
  first = 1;

  if(argc == 3) {
    if(str_is_nan(argv[1]) || str_is_nan(argv[2])) {
      print_error("%s: an input is not a number", argv[0]);
      return 1;
    }

    first = atol(argv[1]);
    last = atol(argv[2]);
    increment = 1;
  }

  if(argc == 4) {
    if(str_is_nan(argv[1]) || str_is_nan(argv[2]) || str_is_nan(argv[3])) {
      print_error("%s: an input is not a number", argv[0]);
      return 1;
    }

    first = atol(argv[1]);
    increment = atol(argv[2]);
    last = atol(argv[3]);
  }

  if(argc > 4) {
    print_error("%s: too many arguments", argv[0]);
    return 1;
  }

  /*
  if(increment == '\0')
    increment = 1;

  if(last == '\0')
    last = 1;
  */

  for(int i = first; i <= last; i+=increment) {
    printf("%d\n", i);
  }

	return 0;
}
