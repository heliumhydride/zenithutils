#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
//#include <string.h>

#define STB_DS_IMPLEMENTATION
#include "../include/stb_ds.h"

#include "../include/prettyprint.h"
#include "../include/util.h"
// #include "../config.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-f] [-s float] [-n int] [-v|-q]\n", argv0);
}

// TODO tail -f, make use of -s

int main(int argc, char* argv[]) {
  char* program = argv[0];
  char mode = 'n';
  long num = 10; // default: -n10
  int verbosity = 1; // quiet:0 normal:1 full:2
  int fflag = 0; // follow file output
  float sleep_interval = 1.0f; // in seconds

  char* endptr;
  int opt;
  while((opt = getopt(argc, argv, ":n:s:fqv")) != -1) {
    switch(opt) {
      case 'c': // fallthrough
      case 'n':
        mode = (char)opt;
        num = strtol(optarg, &endptr, 10);
        if(endptr == optarg) {
          print_error("%s: %s: not an integer", program, optarg);
          return 1;
        }
        break;
      case 's':
        sleep_interval = strtof(optarg, &endptr);
        if(endptr == optarg) {
          print_error("%s: %s: not a floating point number", program, optarg);
          return 1;
        }
        break;
      case 'f':
        fflag = 1;
        break;
      case 'q':
        verbosity = 0;
        break;
      case 'v':
        verbosity = 2;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", program, optopt);
        print_usage(program);
        return 1;
        break;
      case ':':
        print_error("%s: option '%c' needs an argument", program, optopt);
        print_usage(program);
        return 1;
        break;
    }
  }

  argc -= optind;
  argv += optind - 1;

  if(argc == 0) {
    argv--;
    argv[1] = "-";
  }

  FILE* fp;
  while(*++argv) {
    fp = stdin;
    if(strcmp(*argv, "-"))
      fp = fopen(*argv, "r");

    if(fp == NULL) {
      fprintf(stderr, "%s: %s: could not open file", program, *argv);
      return 1;
    }

    if(verbosity == 2)
      printf("==> %s <==\n", (fp == stdin) ? "standard input" : *argv);

    if(mode == 'c') {
      long i = 0;
      int c;
      while((c = fgetc(fp)) != EOF) {
        if(i > num) putchar(c);
        i++;
      }
    } else {
      size_t cap = 0;
      char* line = NULL;
      char** line_list = NULL;
      while(getline(&line, &cap, fp) != -1) {
        char* line2 = malloc(strlen(line) + 1);
        if(line2 == NULL) {
          print_error("%s: malloc() failed", program);
          return 2;
        }
        strcpy(line2, line);
        stbds_arrput(line_list, line2);
      }
      size_t n_lines = arrlenu(line_list);
      for(size_t i = n_lines - num; i < n_lines; i++)
        printf("%s", line_list[i]);
      stbds_arrfree(line_list);
    }

    if(fp != stdin)
      fclose(fp);

    if(argc >= 2)
      putchar('\n');
  }

  return 0;
}
