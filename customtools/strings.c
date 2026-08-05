#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include "../include/prettyprint.h"
#include "../include/util.h"
#include "../config.h"

// TODO radix

void print_usage(char* program) {
  fprintf(stderr, "usage: %s [-nf] file [files ...]\n", program);
  // fprintf(stderr, "usage: %s [-nfo] [-t o|d|x] file [files ...]\n", program);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];

  long min_strlen = 4;
  int fflag = 0;
  // int tflag = 0;
  // char* tmode;

  int opt;
  while((opt = getopt(argc, argv, ":n:t:fo")) != -1) {
    switch(opt) {
      case 'n':
        min_strlen = atol(optarg);
        if(str_is_nan(optarg) || min_strlen <= 0) {
          print_error("%s: '%s': not a positive integer", program, optarg);
          return 1;
        }
        break;
      case 'f':
        fflag = 1;
        break;
      /*
      case 't':
        tflag = 1;
        tmode = optarg;
        if(tmode == NULL) {
          print_error("%s option '-t' requires an argument", argv[0]);
          return 1;
        }
        break;
      case 'o':
        tflag = 1;
        tmode = "o";
        break;
      */
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
    }

    fclose(fp);
  }


  return 0;
}
