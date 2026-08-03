#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sodium.h>
#include "../include/prettyprint.h"
#include "../include/util.h"
#include "../config.h"

// TODO sha512sum -b, -t, -c, -z

void print_usage(const char* program) {
  fprintf(stderr, "usage: %s [file] ...", program);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];
  
  if(sodium_init() == -1) {
    print_error("%s: sodium_init() failed", program);
    return 1;
  }

  if(argc < 2) {
    argv--;
    argv[1] = "-";
  }

  FILE* fp;
  while(*++argv) {
    fp = stdin;
    if(strcmp(*argv, "-")) {
      fp = fopen(*argv, "r");
      if(fp == NULL) {
        print_error("%s: %s: could not open file", program, *argv);
        return 1;
      }
    }

    char* in;
    if(fp == stdin)
      in = malloc(STDIN_MAX);
    else
      in = malloc(get_filesize(fp));

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

    unsigned char out[crypto_hash_sha512_BYTES]; // i know it's always 64, but libsodium provides a constant so let's use it
    if(crypto_hash_sha512(out, (const unsigned char*)in, (unsigned long long)strlen(in)) != 0) {
      print_error("%s: failed to hash", program);
      return 1;
    }
    free(in);

    char* filename = "-";
    if(fp != stdin)
      filename = *argv;

    for(size_t i = 0; i < crypto_hash_sha512_BYTES; i++)
      printf("%02x", out[i]);
    printf("  %s\n", filename);
  }
  return 0;
}
