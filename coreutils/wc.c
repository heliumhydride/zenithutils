#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include "../include/prettyprint.h"

// TODO if multiple arguments then show total
// TODO format output columns correctly

void print_usage(char* program) {
  fprintf(stderr, "usage: %s [-lwcm] [file1] [file2] ...\n", program);
}

int is_continuation(char byte) {
  // in utf-8, 2nd, 3rd and 4th bytes start with 10xxxxxx
  return (byte & 0xC0) == 0x80;
}

void do_counts(FILE* fp, size_t* lines, size_t* words, size_t* bytes, size_t* chars) {
  int inside_word = 0;
  int c;
  while((c = fgetc(fp)) != EOF) {
    bytes[0]++;

    if(c == '\n')
      lines[0]++;

    if(!is_continuation(c))
      chars[0]++;

    if(isspace(c)) {
      inside_word = 0;
    } else {
      if (!inside_word) {
        words[0]++;
        inside_word = 1;
      }
    }
  }
}

size_t count_words(FILE* fp) {
  size_t count = 0;
  int c;
  int inside_word = 0;
  while((c = fgetc(fp)) != EOF) {
    if(isspace(c)) {
      inside_word = 0;
    } else {
      if (!inside_word) {
        count++;
        inside_word = 1;
      }
    }
  }
  fseek(fp, 0L, SEEK_SET);
  return count;
}

int main(int argc, char* argv[]) {
  char* program = argv[0];

  int lflag = 0;
  int wflag = 0;
  int cflag = 0;
  int mflag = 0;

  int use_option = 0;
  int opt;
  while((opt = getopt(argc, argv, ":lwcm")) != -1) {
    use_option = 1;
    switch(opt) {
      case 'l': // count lines (== count linebreaks)
        lflag = 1;
        break;
      case 'w': // count words (count spaces+1)
        wflag = 1;
        break;
      case 'c': // count bytes
        cflag = 1;
        break;
      case 'm': // count characters
        mflag = 1;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'\n", program, optopt);
        print_usage(program);
        return 1;
        break;
    }
  }
  
  argv += optind - 1;
  if(!use_option) // default for wc is -lwc
    lflag = wflag = cflag = 1;

  if(argc == optind) {
    argv--; // To avoid trying to wc 'SHELL=/bin/bash', was trying to pull beyond argv
    argv[1] = "-";
  }

  FILE* fp;
  while(*++argv) {
    fp = stdin;
    if(strcmp(*argv, "-"))
      fp = fopen(*argv, "rb");

    if(fp == NULL) {
      print_error("%s: %s: File not found\n", program, *argv);
    }

    size_t lines, words, chars, bytes;
    lines = words = chars = bytes = 0;
    do_counts(fp, &lines, &words, &chars, &bytes);
    if(lflag)
      printf(" %zu ", lines);
    if(wflag)
      printf(" %zu ", words);
    if(mflag)
      printf(" %zu ", chars);
    if(cflag)
      printf(" %zu ", bytes);
    printf("%s\n", *argv);
    
    if(strcmp(*argv, "-"))
      fclose(fp);
  }
  return 0;
}
