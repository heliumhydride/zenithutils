#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "../include/prettyprint.h"
#include "../include/util.h"

void print_usage(char* program) {
  fprintf(stderr, "usage: %s [-c num | -n num] [file] [file2] ...", program);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];
  long num = 10;
  char mode = 'n';
  int opt;
  while((opt = getopt(argc, argv, "c:n:")) != -1) {
    switch(opt) {
      case 'c': // fallthrough; first n bytes
      case 'n': //              first n lines
        mode = (char)opt;
        num = strtol(optarg, NULL, 10);
        break;
      case ':':
        print_error("%s: option '-%c' needs an argument", program, optopt);
        print_usage(program);
        return 1;
        break;
      case '?':
        print_error("%s: invalid option -- '-%c'", program, optopt);
        print_usage(program);
        return 1;
        break;
    }
  }
  
  argv += optind - 1;
  if(argc == optind) {
    argv--;
    argv[1] = "-";
  }

  FILE* fp;
  while(*++argv) {
    fp = stdin;
    if(strcmp(*argv, "-"))
      fp = fopen(*argv, "r");

    if(fp == NULL) {
      fprintf(stderr, "%s: %s: no such file", program, *argv);
      return 1;
    }

    if(mode == 'c') {
      long i = 0;
      int c;
      while((c = fgetc(fp)) != EOF && i < num) {
        printf("%c", c);
        i++;
      }
    } else {
      size_t cap = 0;
      long i = 0;
      char* line = NULL;
      while(getline(&line, &cap, fp) != -1 && i < num) {
        printf("%s", line);
        i++;
      }
    }

    if(fp != stdin)
      fclose(fp);
  }

  return 0;
}
