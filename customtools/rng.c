#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
//#include <stdlib.h>
//#include <getopt.h>
//#include <unistd.h>
//#include <string.h>

#include "../include/prettyprint.h"
#include "../include/util.h"
#include <sodium.h>

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [min] max\n", argv0);
}

int main(int argc, char* argv[]){
  ssize_t min;
  ssize_t max;

  if (sodium_init() == -1) {
    print_error("%s: sodium_init() failed", argv[0]);
    return 1;
  } 

  if(argc <= 1) { // We have no arg
    print_usage(argv[0]);
    return 1;
  }
  
  if(argc == 2) { // We have one arg, default min to 0
    min = 0;

    if(str_is_nan(argv[1])) {
      print_error("%s: '%s' is not a number", argv[0], argv[1]);
      return 1;
    }
    max = atol(argv[1]);
  }

  if(argc >= 3){ // We have 2+ args
    if(str_is_nan(argv[1])) {
      print_error("%s: '%s' is not a number", argv[0], argv[1]);
      return 1;
    }
    min = atol(argv[1]);

    if(str_is_nan(argv[2])) {
      print_error("%s: '%s' is not a number", argv[0], argv[2]);
      return 1;
    }
    max = atol(argv[2]);
  }
  
  printf("%ld\n", randombytes_uniform(max-min) + min);
  return 0;
}
