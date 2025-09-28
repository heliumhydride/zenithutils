#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
//#include <getopt.h>
#include <unistd.h>
//#include <string.h>

#ifdef _WIN32
#include "windows.h"
#endif

#include "../include/prettyprint.h"

/*
void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s", argv0);
}
*/

int main(int argc, char* argv[]){
  char* username = NULL;

  #ifdef _WIN32
  // that's right we're gonna cheat (using the environment variable USERNAME)
  username = getenv("USERNAME");
  #else // On Unix
  // TODO when i run "su root" and then run o/usr/bin/whoami, it shows my username before running su instead of "root"... [probably because this acts like logname and not whoami]
  username = getlogin();
  #endif

  if(username == NULL) {
    print_error("%s: getting username failed", argv[0]);
    return 1;
  }
  printf("%s\n", username);
  return 0;
}
