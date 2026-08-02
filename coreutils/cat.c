#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "../include/prettyprint.h"
#include "../include/util.h"

void print_usage(char* program) {
  fprintf(stderr, "usage: %s [-AEenTtv] [file1] [file2] ...\n", program);
}

// TODO unicode compat for *filter() ?

char* Efilter(const char *s) {
  if(s == NULL)
    return NULL;

  size_t extra = 0;
  for(const char* p = s; *p != '\0'; p++) {
    if(*p == '\n')
      extra++;
  }

  size_t len = strlen(s);
  char* out = malloc(len + extra + 1);
  if(out == NULL)
    return NULL;

  char* w = out;
  for(const char* p = s; *p; p++) {
    if (*p == '\n') {
      *w++ = '$';
      *w++ = '\n';
    } else {
      *w++ = *p;
    }
  }
  *w = '\0'; // finish string
  return out;
}

char* Tfilter(const char *s) {
  if(s == NULL)
    return NULL;

  size_t extra = 0;
  for(const char* p = s; *p != '\0'; p++) {
    if(*p == '\n')
      extra++;
  }

  size_t len = strlen(s);
  char* out = malloc(len + extra + 1);
  if(out == NULL)
    return NULL;

  char* w = out;
  for(const char* p = s; *p; p++) {
    if (*p == '\t') {
      *w++ = '^';
      *w++ = 'I';
    } else {
      *w++ = *p;
    }
  }
  *w = '\0'; // finish string
  return out;
}

int isnonprint(char c) {
  if(c >= 0 && c < 0x20)
    return 1;
  if(c == 0x7f)
    return 1;
  return 0;
}

char* vfilter(const char *s) {
  if(s == NULL)
    return NULL;

  size_t extra = 0;
  for(const char* p = s; *p != '\0'; p++) {
      if(isnonprint(*p))
        extra++;
  }

  size_t len = strlen(s);
  char* out = malloc(len + extra + 1);
  if(out == NULL)
    return NULL;

  char* w = out;
  for (const char* p = s; *p; p++) {
    if (*p == '\0') { // NULL
      *w++ = '^';
      *w++ = '@';
    } else if(*p == 0x7f) { // DEL
      *w++ = '^';
      *w++ = '?';
    } else if(*p >= 0x01 && *p <= 0x1F && *p != '\t' && *p != '\n') {
      *w++ = '^';
      *w++ = *p+64;
    } else {
      *w++ = *p;
    }
  }
  *w = '\0'; // finish string
  return out;
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
      case 'n':
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
        print_error("%s: option error: unknown option '-%c'", program, optopt);
        print_usage(program);
        return 1;
        break;
    }
  }

  argv += optind - 1;

  if(optind == argc) {
    argv--; // see coreutils/wc.c
    argv[1] = "-";
  }

  FILE* fp;
  while(*++argv) {
    fp = stdin;
    if(strcmp(*argv,"-"))
      fp = fopen(*argv, "rb");
    
    if(fp == NULL) {
      print_error("%s: %s: File not found", program, *argv);
      return 1;
    }

    char* line = NULL;
    size_t count = 1;
    size_t cap = 0;
    while(getline(&line, &cap, fp) != -1) {
      if(nflag) printf("%5zu  ", count);
      char *orig = line;

      if(Eflag) {
        line = Efilter(orig);
        free(orig);
        orig = line;
      }
      if(Tflag) {
        line = Tfilter(orig);
        free(orig);
        orig = line;
      }
      if(vflag) {
        line = vfilter(orig);
        free(orig);
        orig = line;
      }

      printf("%s", line);
      free(line);
      line = NULL;
      count++;
    }
    free(line);

    if(strcmp(*argv,"-"))
      fclose(fp);
  }
  return 0;
}
