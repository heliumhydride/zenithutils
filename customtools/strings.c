#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include "../include/prettyprint.h"
#include "../include/util.h"
#include "../config.h"

void print_usage(char* program) {
  fprintf(stderr, "usage: %s [-nfo] [-t o|d|x] file [files ...]\n", program);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];

  long min_strlen = 4;
  int fflag = 0;
  int tflag = 0;
  char tmode;

  int opt;
  while((opt = getopt(argc, argv, ":n:t:fo")) != -1) {
    switch(opt) {
      case 'n':
        min_strlen = atol(optarg) - 1;
        if(str_is_nan(optarg) || min_strlen <= 0) {
          print_error("%s: '%s': not a positive integer", program, optarg);
          return 1;
        }
        break;
      case 'f':
        fflag = 1;
        break;
      case 't':
        tflag = 1;
        tmode = optarg[0];
        switch(tmode) {
          case 'x': // fall
          case 'd': // fall
          case 'o': // fall
            break;
          default:
            print_error("%s: invalid radix '%s'", program, optarg);
            print_usage(program);
            return 1;
            break;
        }
        break;
      case 'o':
        tflag = 1;
        tmode = 'o';
        break;
      case '?':
        print_error("%s: invalid option -- '-%c'", program, optopt);
        print_usage(program);
        return 1;
        break;
      case ':':
        print_error("%s: option '-%c' requires an argument", program, optopt);
        print_usage(program);
        return 1;
        break;
    }
  }

  argc -= optind;
  argv += optind - 1;

  if(argc == 0) { // no file arg provided
    print_usage(program);
    return 1;
  }

  char buf[STRING_MAXSTRLEN] = {0};
  while(*++argv) {
    FILE* fp = fopen(*argv, "rb");
    if(fp == NULL) {
      fprintf(stderr, "%s: %s: could not open file", program, *argv);
      return 1;
    }

    long i = 0;
    long offset = 0;
    int c;
    while((c = fgetc(fp)) != EOF) {
      if(isprint(c)) {
        if(i > min_strlen)
          putchar(c);
        else {
          buf[i] = (char)c;
          if(i == min_strlen) {
            if(fflag)
              printf("%s:  ", *argv);
            if(tflag) {
              switch(tmode) {
                case 'x':
                  printf("%lx ", offset - i);
                  break;
                case 'd':
                  printf("%ld ", offset - i);
                  break;
                case 'o':
                  printf("%lo ", offset - i);
                  break;
              }
            }
            printf("%s", buf);
          }
          i++;
        }
      } else {
        memset(buf, 0, STRING_MAXSTRLEN);
        if(i > min_strlen)
          putchar('\n');
        i = 0;
      }
      offset++;
    }
    fclose(fp);
  }
  return 0;
}
