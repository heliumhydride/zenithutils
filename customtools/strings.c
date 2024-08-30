#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
//#include <unistd.h>
//#include <string.h>

#include "../include/prettyprint.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s file [files ...]\n", argv0);
}

int main(int argc, char* argv[]){
  int opt;

  int tflag = 0;
  char* tmode;
  int fflag = 0;

  // TODO: Getopt options
  while((opt = getopt(argc, argv, ":nt:fo")) != -1) {
    switch(opt) {
      case 'n':
        break;
      case 't':
        tflag = 1;
        tmode = optarg;
        if(tmode == NULL) {
          print_error("%s option '-t' requires an argument", argv[0]);
          return 1;
        }
        break;
      case 'f':
        fflag = 1;
        break;
      case 'o':
        tflag = 1;
        tmode = "o";
        break;
      case '?':
        print_error("%s: invalid option -- '%c'\n", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  if(argc==optind) { // no file arg provided
    print_usage(argv[0]);
    return 1;
  }

  FILE* fileptr;
  fileptr = fopen(argv[optind], "r");

  if(fileptr == NULL) {
    print_error("%s: could not open file '%s'", argv[0], argv[optind]);
    return 1;
  }

  size_t filesize;
  if(fseek(fileptr, 0L, SEEK_END) == 0) {
    filesize = ftell(fileptr);
    if(filesize == -1) {
      print_error("%s: ftell() failed", argv[0]);
      return 1;
    }
  }

  char* buf = malloc(sizeof(char) * (filesize + 1));

  if(fseek(fileptr, 0L, SEEK_SET) != 0) {
    print_error("%s: fseek() failed\n");
  }

  size_t newlen = fread(buf, sizeof(char), filesize, fileptr);
  if(ferror(fileptr) != 0) {
    print_error("%s: reading file \"%s\" failed", argv[0], argv[optind]);
  } else {
    buf[newlen++] = '\0';
  }

  fclose(fileptr);
  // TODO: Split each string, not characters (to put filename before each line/string via -f option)
  char ch;
  for(int i = 0; i < filesize; i++) {
    ch = buf[i];
    switch(ch) {
      case ' ': case '!': case '#': case '$': case '%':
      case '&': case '\'': case '(': case ')': case '*':
      case '+': case ',': case '-': case '.': case '/':
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
      case ':': case ';': case '<': case '=': case '>':
      case '?': case '@': case 'A': case 'B': case 'C':
      case 'D': case 'E': case 'F': case 'G': case 'H':
      case 'I': case 'J': case 'K': case 'L': case 'M':
      case 'N': case 'O': case 'P': case 'Q': case 'R':
      case 'S': case 'T': case 'U': case 'V': case 'W':
      case 'X': case 'Y': case 'Z': case '[': case '\\':
      case ']': case '^': case '_': case '`': case 'a':
      case 'b': case 'c': case 'd': case 'e': case 'f':
      case 'g': case 'h': case 'i': case 'j': case 'k':
      case 'l': case 'm': case 'n': case 'o': case 'p':
      case 'q': case 'r': case 's': case 't': case 'u':
      case 'v': case 'w': case 'x': case 'y': case 'z':
      case '{': case '|': case '}': case '~': case '\"':
      case '\n': case '\t':
        printf("%c", ch);
        break;
    }
  }

  free(buf);
	return 0;
}
