#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
//#include <string.h>

#include "../include/prettyprint.h"
#include "../include/util.h"
#include <sodium.h>

char* charset = "0123456789abcdef";

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-C num] | [-h]\n", argv0);
}

char* uuidgen() {
  char* uuid = malloc(36);

  for(int i = 0; i < 8; i++)
    uuid[i] = charset[randombytes_uniform(16)];

  for(int i = 0; i < 4; i++)
    uuid[i+9] = charset[randombytes_uniform(16)];

  for(int i = 0; i < 4; i++)
    uuid[i+14] = charset[randombytes_uniform(16)];

  for(int i = 0; i < 4; i++)
    uuid[i+19] = charset[randombytes_uniform(16)];

  for(int i = 0; i < 12; i++)
    uuid[i+24] = charset[randombytes_uniform(16)];

  // Add the separators
  uuid[8] = uuid[13] = uuid[18] = uuid[23] = '-';
  return uuid;
}

int main(int argc, char* argv[]) {
  int opt;
  size_t count = 1;

  if(sodium_init() < 0) {
    print_error("%s: libsodium sodium_init failed", argv[0]);
    return 1;
  }

  while((opt = getopt(argc, argv, ":C:h")) != -1) {
    switch(opt) {
      case 'C':
        if(str_is_nan(optarg) || atol(optarg) <= 0) {
          print_error("%s: '%s' is not a positive number", argv[0], optarg);
          return 1;
        }
        count = atol(optarg);
        break;
      case 'h':
        print_usage(argv[0]);
        return 0;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }
  
  for(int i = 0; i < count; i++)
    printf("%s\n", uuidgen());

  return 0;
}
