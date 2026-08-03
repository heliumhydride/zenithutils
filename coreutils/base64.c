#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sodium.h>
#include "../include/prettyprint.h"
#include "../include/util.h"
#include "../config.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-d] [file]\n", argv0);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];

  if(sodium_init() == -1) {
    print_error("%s: sodium_init() failed", program);
    return 1;
  }

  int dflag = 0; // decode mode
  int opt;
  while((opt = getopt(argc, argv, ":d")) != -1) {
    switch(opt) {
      case 'd':
        dflag = 1;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", program, optopt);
        print_usage(program);
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

  char* in;
  if(fp == stdin) {
    in = malloc(STDIN_MAX);
  } else {
    in = malloc(get_filesize(fp));
  }

  if(in == NULL) {
    print_error("%s: malloc() failed", program);
    return 2;
  }

  size_t i = 0;
  int c;
  while((c = fgetc(fp)) != EOF) {
    in[i] = c;
    i++;
  }
  if(fp != stdin)
    fclose(fp);

  size_t out_maxlen;
  if(dflag)
    out_maxlen = strlen(in);
  else
    out_maxlen = sodium_base64_encoded_len(strlen(in), BASE64_VARIANT);

  char* out = malloc(out_maxlen);
  if(dflag) {
    size_t outlen;
    const char* endptr;
    if(sodium_base642bin((unsigned char*)out, out_maxlen, in, strlen(in), BASE64_IGNORE, &outlen, &endptr, BASE64_VARIANT) == -1) {
      print_error("decoding failed\n");
      return 1;
    }
  } else {
    if(sodium_bin2base64(out, out_maxlen, (unsigned char*)in, strlen(in), BASE64_VARIANT) == NULL) {
      print_error("%s: encoding failed", program);
      return 1;
    }
  }

  puts(out);
  free(out);
  return 0;
}
