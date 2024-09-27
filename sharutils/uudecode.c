#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include <string.h>

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-m] [-p | -o outfile] [encodedfile ...]", argv0);
}

char* uudecode(char* in) {
  char* buf;
  // TODO: uudecode from 'in' to 'buf'
  return buf;
}

int main(int argc, char* argv[]){
  int opt;
  int mode = 1; // 1 = uuencode format; 2 = base64 format
  int output = 0; // 0 = none; 1 = stdout; 2 = to outfile

  while((opt = getopt(argc, argv, ":mp:o")) != -1) {
    switch(opt) {
      case 'm':
        mode = 2;
        break;
      case 'p':
        output = 1;
        break;
      case 'o':
        output = 2;
        char* outfilename;
        // TODO get optarg for 'o' to 'outfilename'
        break;
      case '?':
        printf("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  // TODO: get inputfile filename (if any, if not use stdin) from argv

  switch(mode) {
    case 1: // uuencode format
      break;
    case 2: // base64 format
      break;
  }

  return 0;
}
