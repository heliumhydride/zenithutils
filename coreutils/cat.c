#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "../include/prettyprint.h"

void print_usage(char* program) {
  fprintf(stderr, "usage: %s [-AEenTtv] [file1] [file2] ...\n", program);
}

void vfilter(char* out, char c) {
  // takes a non printable character and returns a string representing it
  if(c == '\0') { // NUL
    out[0] = '^'; out[1] = '@';
  } else if(c == 0x7F) { // DEL
    out[0] = '^'; out[1] = '?';
  } else if(c >= 0x01 && c <= 0x1F && c != '\t' && c != '\n') {
    out[0] = '^'; out[1] = c+64;
  } else {
    out[0] = c;
    out[1] = '\0';
  }
}

int main(int argc, char* argv[]) {
  char* program = argv[0];

  int Eflag = 0;
  int Tflag = 0;
  int vflag = 0;
  int nflag = 0;
  int opt;
  while((opt = getopt(argc, argv, ":AEenTtv")) != -1) {
    switch(opt) {
      case 'A':
        vflag = Eflag = Tflag = 1;
        break;
      case 'E':
        Eflag = 1;
        break;
      case 'e':
        vflag = Eflag = 1;
        break;
      case 'n': // TODO cat -n
        nflag = 1;
        break;
      case 'T':
        Tflag = 1;
        break;
      case 't':
        vflag = Tflag = 1;
        break;
      case 'v':
        vflag = 1;
        break;
      case '?':
        fprintf(stderr, "%s: option error: unknown option \"-%c\"\n", program, optopt);
        print_usage(program);
        return 1;
        break;
    }
  }

  argv += optind - 1;

  if(optind == argc) { // probably very sketchy and unsafe ?
    argv[1] = "-";
  }

  FILE* fp;
  while(*++argv) {
    fp = stdin;
    if(strcmp(*argv,"-"))
      fp = fopen(*argv, "rb");
    
    if(fp == NULL) {
      print_error("%s: %s: File not found\n", program, *argv);
      return 1;
    }

    int c;
    while((c = fgetc(fp)) != EOF) {
      if(Tflag && c == '\t') {
        printf("^I");
      } else if(Eflag && c == '\n') {
        printf("$\n");
      } else if(vflag) {
        char s[2];
        vfilter(s,c);
        printf("%s", s);
      } else {
        printf("%c", c);
      }
    }

    fclose(fp);
  }
  return 0;
}
