#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "../include/prettyprint.h"
#include "../config.h"

void print_usage(char* program) {
  fprintf(stderr, "usage: %s [-f fmt] [-s sep] last\n", program);
  fprintf(stderr, "       %s [-f fmt] [-s sep] first last\n", program);
  fprintf(stderr, "       %s [-f fmt] [-s sep] first increment last\n", program);
}

int is_sane_fmt(const char* fmt) {
  int has_directive = 0;
  int in_directive = 0;
  char* fmt2 = (char*)fmt;
  while(*fmt2) {
    if(*fmt2 == '%') { // we started a directive
      has_directive++;
      in_directive = 1;
      fmt2++;
    }

    if(has_directive >= 2) // eg. '%f%f' banned
      return 0;

    if(in_directive) {
      switch(*fmt2) {
        case '+':
        case '-':
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case 'f':
        case 'F':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
        case 'A':
        case 'a':
          fmt2++;
          in_directive = 0;
          break;
        case '%': 
          has_directive--; // because '%%' is fine
          fmt2++;
          in_directive = 0;
          break;
        default:
          return 0;
      }
    }

    if(!in_directive) // not in a directive = nothing to see here, keep going
      fmt2++;
  }
  #if STRICT_SEQ
  if(!has_directive) // see config.h
    return 0;
  #endif // STRICT_SEQ
  return 1;
}

int main(int argc, char* argv[]) {
  char* program = argv[0];

  char* fmt = "%g";
  char* sep = "\n";
  int wflag = 0;

  float first = 1.0f;
  float increment = 1.0f;
  float last = 1.0f;

  while(1) {
    if(optind >= argc)
      break;

    // check for negative numbers, don't count them
    // TODO what if we use numbers at the start
    // NOTE do be fair it seems like gnu seq has the same issue...
    char* a = argv[optind];
    if(a[0] == '-' && a[1] && a[1] >= '0' && a[1] <= '9')
      break;

    int opt = getopt(argc, argv, ":f:s:w");
    if(opt == -1)
      break;
    switch(opt) {
      case 'f': // set format for printf, default is "%g"
        fmt = optarg;
        break;
      case 's': // separator, default is newline
        sep = optarg;
        break;
      case 'w': // TODO
        wflag = 1;
        break;
      case ':':
        print_error("%s: option '-%c' needs an argument", program, optopt);
        print_usage(program);
        return 1;
        break;
      case '?':
        print_error("%s: option error: unknown option '-%c'", program, optopt);
        print_usage(program);
        return 1;
        break;
    }
  }

  argc -= optind;
  argv += optind - 1;

  char* endptr;
  switch(argc) {
    case 0: // no arg
      print_error("%s: missing operand", program);
      print_usage(program);
      return 1;
      break;
    case 1: // just last
      last = strtof(argv[1], &endptr);
      if(endptr == argv[1]) {
        print_error("%s: %s: not a number", program, argv[1]);
        return 1;
      }
      break;
    case 2: // first last
      first = strtof(argv[1], &endptr);
      if(endptr == argv[1]) {
        print_error("%s: %s: not a number", program, argv[1]);
        return 1;
      }

      last = strtof(argv[2], &endptr);
      if(endptr == argv[2]) {
        print_error("%s: %s: not a number", program, argv[2]);
        return 1;
      }
      break;
    case 3: // first increment last
      first = strtof(argv[1], &endptr);
      if(endptr == argv[1]) {
        print_error("%s: %s: not a number", program, argv[1]);
        return 1;
      }

      increment = strtof(argv[2], &endptr);
      if(endptr == argv[2]) {
        print_error("%s: %s: not a number", program, argv[2]);
        return 1;
      }

      last = strtof(argv[3], &endptr);
      if(endptr == argv[3]) {
        print_error("%s: %s: not a number", program, argv[3]);
        return 1;
      }
      break;
    default:
      print_error("%s: trailing arguments", program);
      return 1;
  }

  // sanity checks
  if(increment == 0) {
    print_error("%s: refusing zero increment", program);
    return 1;
  }
  if(!is_sane_fmt(fmt)) {
    print_error("%s: insane fmt '%s', incorrect for a single floating point numbers", program, fmt);
    return 1;
  }

  if(increment >= 0){
    for(float i = first; i <= last; i+=increment) {
      printf(fmt, i);
      printf("%s", sep);
    }
  } else {
    for(float i = first; i >= last; i+=increment) {
      printf(fmt, i);
      printf("%s", sep);
    }
  }
  if(strcmp(sep, "\n"))
    putchar('\n');

  return 0;
}
