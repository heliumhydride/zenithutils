#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/util.h"
#include "../include/prettyprint.h"

void rev(char* out, char* in) {  
  size_t size = strlen(in);
  int had_newline = 0;
  if(in[size-1] == '\n') {
    had_newline = 1;
    in--;
  }

  for(size_t i = 0; i < size; i++)
    out[i] = in[size-1-i];
  
  if(had_newline)
    out[size-1] = '\n';
}

void print_usage(const char* program) {
  fprintf(stderr, "usage: %s [file] [file2] ...\n", program);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];
  FILE* fp = stdin;
  if(argc < 2) {
    argv--;
    argv[1] = "-";
  }

  while(*++argv) {
    if(strcmp(*argv, "-"))
      fp = fopen(*argv, "r");

    if(fp == NULL) {
      print_error("%s: %s: no such file", program, *argv);
      return 1;
    }

    char* line = NULL;
    size_t cap = 0;
    while(getline(&line, &cap, fp) != -1) {
      char* line_rev = malloc(strlen(line)+1);
      if(line_rev == NULL)
        return 2;
      rev(line_rev, line);
      printf("%s", line_rev);
    }

    if(fp != stdin)
      fclose(fp);
  }
  return 0;
}
