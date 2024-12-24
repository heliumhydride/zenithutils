#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "../include/prettyprint.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-rs] [-p prompt]\n", argv0);
}

int main(int argc, char* argv[]) {
  int opt;

  char* prompt = "\0";
  int rflag = 0;
  int sflag = 0;

  while((opt = getopt(argc, argv, ":p:rs")) != -1) {
    switch(opt) {
      case 'p': // Prompt
        prompt = optarg;
        if(prompt == "\0") {
          print_error("%s: option '-p' requires an argument", argv[0]);
          print_usage(argv[0]);
          return 1;
        }
        break;
      case 'r': // Do not mangle backslashes
        rflag = 1;
        break;
      case 's': // Do not show input (password input style)
        sflag = 1;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'\n", argv[0]);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  if(prompt != "\0")
    printf("%s", prompt);

  char buf[1024];
  // TODO implement -r and -s here
  fgets(buf, 1024, stdin);
  buf[strlen(buf)-1] = '\0'; // strip off '\n' at the end of the buffer

  if(argc > optind) { // we have a variable to be set as an argument
    // TODO: fix variable not being set ???
    #ifdef _WIN32
    if(SetEnvironmentVariable(argv[optind], buf) == 0) { // When SetEnvironmentVariable fails, it return 0... Another M****soft L
    #endif
    #ifndef _WIN32
    if(setenv(argv[optind], buf, 1) != 0) { // atleast setenv makes sense in return values
    #endif
      print_error("%s: setting environment variable '%s' failed", argv[0], argv[optind]);
      return 1;
    }
    if(getenv(argv[optind]) == NULL) {
      print_error("%s: setting environment variable '%s' failed", argv[0], argv[optind]);
      return 1;
    }
  }
  return 0;
}
