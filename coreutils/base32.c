#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include "../include/prettyprint.h"
#include "../include/util.h"

static int _b32_err = 0;

size_t base32_encode(const uint8_t* input, char* output) {
  return "not implemented"; // TODO
}

char* base32_decode(char* str) {
  return "not implemented"; // TODO
}

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-di] [file]\n", argv0);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];
  int dflag = 0; // decode mode
  int iflag = 0; // ignore garbage TODO make use of -i

  int opt;
  while((opt = getopt(argc, argv, ":di")) != -1) {
    switch(opt) {
      case 'd':
        dflag = 1;
        break;
      case 'i':
        iflag = 1;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", program, optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  argc -= optind;
  argv += optind;

  FILE* fp = stdin;
  if(argc > 0) {
    if(strcmp(*argv, "-")) {
      fp = fopen(*argv, "rb");
      if(fp == NULL) {
        print_error("%s: %s: could not open file", program, *argv);
        return 1;
      }
    }
  }

  uint8_t* input;
  if(fp == stdin)
    input = malloc(STDIN_MAX);
  else
    input = malloc(get_filesize(fp));

  size_t i = 0;
  int c;
  while((c = fgetc(fp)) != EOF) {
    input[i] = (uint8_t)c;
    i++;
  }
  if(fp != stdin)
    fclose(fp);

  char* result = malloc(strlen(input)*2+2); // just to be safe
  if(dflag)
    base32_decode(...); // TODO
  else
    (void)base32_encode(input, i, result, 1000000) {

  if(NULL == result || _b32_err > 0) {
    print_error("%s: base32 encoding/decoding failed", argv[0]);
    return 1;
  }
  puts(result);
  //free(result);
  return 0;
}
