#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "../include/prettyprint.h"

void mingw_path(char* path) {
  for(size_t i = 0; i < strlen(path); i++) {
    if(path[i] == '\\')
      path[i] = '/';
  }
}

void win32_path(char* path) {
  for(size_t i = 0; i < strlen(path); i++) {
    if(path[i] == '/')
      path[i] = '\\';
  }
}

void print_usage(char* program) {
  fprintf(stderr, "usage: %s [-mw] path\n", program);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];
  char mode = 'm';
  int opt;
  while((opt = getopt(argc, argv, ":mw")) != -1) {
    switch(opt) {
      case 'w':
        mode = 'w';
        break;
      case '?':
        print_error("%s: option error: unknown option '-%c'", program, optopt);
        print_usage(program);
        return 1;
        break;
    }
  }

  argc -= optind;
  argv += optind;

  if(argc == 0) {
    print_usage(program);
    return 1;
  }

  switch(mode) {
    case 'm':
      mingw_path(*argv);
      break;
    case 'w':
      win32_path(*argv);
      break;
  }
  puts(*argv);
  return 0;
}
