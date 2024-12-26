#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

#include "../include/prettyprint.h"
#include "../include/util.h"

static int _b32_err = 0;

char* base32_encode(char* str) {
  return "not implemented"; // TODO
}

char* base32_decode(char* str) {
  return "not implemented"; // TODO
}

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-di] [file]\n", argv0);
}

int main(int argc, char* argv[]) {
  int opt;
  int dflag = 0; // decode mode
  int iflag = 0; // ignore garbage TODO make use of -i

  while((opt = getopt(argc, argv, ":di")) != -1) {
    switch(opt) {
      case 'd':
        dflag = 1;
        break;
      case 'i':
        iflag = 1;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  char* buf;
  if(argc == optind || argv[1][0] == '-') { // read from stdin if no file or file is '-'
    buf = getbytes_stdin();
    if(NULL == buf) {
      print_error("%s: getbytes_stdin() failed", argv[0]);
      return 1;
    }
  } else { // We read from a file
    FILE* fileptr = fopen(argv[optind], "r");
    if(NULL == fileptr) {
      print_error("%s: could not open file \"%s\"", argv[0], argv[optind]);
      return 1;
    }

    buf = malloc(get_filesize(fileptr)+1);
    if(readfile(fileptr, buf) == -1) {
      print_error("%s: read error", argv[0]);
      return 1;
    }
    fclose(fileptr);
  }

  char* result = malloc(strlen(buf)*2+2); // just to be safe
  if(dflag) { // decoding
    result = base32_decode(buf);
  } else { // encoding
    result = base32_encode(buf);
  }

  if(NULL == result || _b32_err > 0) {
    print_error("%s: base32 encoding/decoding failed", argv[0]);
    return 1;
  }
  
  printf("%s\n", result);
  return 0;
}
