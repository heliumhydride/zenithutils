#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>

#include "../include/prettyprint.h"
#include "../include/util.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s µs\n", argv0);
}

int main(int argc, char* argv[]){
  if(argc <= 1) { // We have no argument
    print_usage(argv[0]);
    return 1;
  }
  if(str_is_nan(argv[1])) { // We have an argument, but it isn't a number
    print_error("%s: '%s' is not a number", argv[0], argv[1]);
    return 1;
  }

  usleep(atol(argv[1]));
	return 0;
}
