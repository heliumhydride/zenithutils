#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "../include/prettyprint.h"

void print_usage(char* program) {
  fprintf(stderr, "usage: %s [-a] [file]", program);
}

// TODO operate line by line instead of char by char (more correct for multiple stdout, makes "abcabc" instead of "aabbcc")

int main(int argc, char* argv[]) {
  char* program = argv[0];
  int aflag;

  int opt;
  while((opt = getopt(argc, argv, ":a")) != -1) {
    switch(opt) {
      case 'a':
        aflag = 1;
        break;
      case '?':
        print_error("%s: option error: unknown option '-%c'", program, optopt);
        print_usage(program);
        return 1;
        break;
    }
  }

  argc -= optind;
  argv += optind - 1;

  char** filenames = argv;
  FILE** files = calloc(argc+1, sizeof(FILE*));
  files[0] = stdout;

  for(int i = 1; i <= argc; i++) {
    files[i] = stdout;
    if(strcmp(filenames[i], "-")) {
      if(aflag)
        files[i] = fopen(filenames[i], "a");
      else
        files[i] = fopen(filenames[i], "w");

      if(files[i] == NULL) {
        print_error("%s: could not open %s", program, filenames[i]);
        free(files);
        return 1;
      }
    }
    setbuf(files[i], NULL);
  };

  // write to files
  int nfiles = (argc == 0) ? 1 : (argc+1); // if we have no arg there's still stdout
  int c;
  while((c = getchar()) != EOF) {
    for(int i = 0; i < nfiles; i++) {
      fputc(c, files[i]);
    }
  }

  for(int i = 0; i < nfiles; i++) {
    if(files[i] != stdout)
      fclose(files[i]);
  }
  free(files);
  return 0;
}
