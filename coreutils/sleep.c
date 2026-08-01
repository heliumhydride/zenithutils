#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../include/prettyprint.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s time\n", argv0);
}

int is_interval(const char* ival) {
  if(ival == NULL)
    return 0;
  
  // check we begin with a positive float
  char* end = NULL;
  float t = strtof(ival, &end);
  if(end == ival || t < 0)
    return 0;

  // check suffixes
  switch(*end) {
    case '\0':
    case 's':
    case 'm':
    case 'h':
    case 'd':
      return 1;
    default:
      return 0;
  }
}

float toseconds(char* ival) {
  if(!is_interval(ival))
    return -1;
  char last = ival[strlen(ival) - 1];
  float multiplier = 1.0f;

  switch(last) {
    case 's': // fall
      ival[strlen(ival) - 1] = '\0';
      break;
    case 'm': // fall
      multiplier = 60.0f;
      ival[strlen(ival) - 1] = '\0';
      break;
    case 'h': // fall
      multiplier = 3600.0f;
      ival[strlen(ival) - 1] = '\0';
      break;
    case 'd':
      multiplier = 86400.0f;
      ival[strlen(ival) - 1] = '\0';
      break;
  }
  return atof(ival) * multiplier;
}

int main(int argc, char* argv[]) {
  if(argc <= 1) {
    print_usage(argv[0]);
    return 1;
  }

  float time = toseconds(argv[1]);
  if(time == -1) {
    print_error("%s: incorrect interval '%s'", argv[0], argv[1]);
    print_usage(argv[0]);
    return 1;
  }
  if(time == 0)
    return 0;

  usleep(time*1000000);
  return 0;
}
