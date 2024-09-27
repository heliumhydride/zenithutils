#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include <string.h>

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-m] [inputfile] headername > encodedfile", argv0);
}

char* uuencode(char* in) {
  char* buf;
  // TODO: uuencode from 'in' to 'buf'
  return buf;
}

int main(int argc, char* argv[]){
  int opt;
  int mode = 1; // 1 = uuencode format; 2 = base64 format

  while((opt = getopt(argc, argv, ":m")) != -1) {
    switch(opt) {
      case 'm':
        mode = 2;
        break;
      case '?':
        printf("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  // TODO: get inputfile filename (if any, if not use stdin) and headername from argv

  char* inputstring
  char* header;

  // TODO: On Unix, get file permissions and add them to the uuencoded output instead of default '644' permissions
  switch(mode) {
    case 1: // uuencode format
      printf("begin 644 %s\n", header);
      printf("%s\n", uuencode(inputstring));
      printf("`\nend\n");
      break;
    case 2: // base64 format
      printf("begin-base64 644 %s\n", header);
      printf("%s\n", base64_encode(inputstring));
      printf("\n====\n");
      break;
  }

  return 0;
}
