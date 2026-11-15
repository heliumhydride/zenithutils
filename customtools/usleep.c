#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <unistd.h>
#include "../include/util.h"

void print_usage(const char* program)
{
  fprintf(stderr, "usage: %s [time in µs]\n", program);
}

int main(int argc, char* argv[])
{
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
