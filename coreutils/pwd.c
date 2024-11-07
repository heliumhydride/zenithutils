#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "../include/prettyprint.h"
#include "../config.h"

#ifdef _WIN32
#include <windows.h>
#endif

void mingw_path(char* out, char* path) {
  size_t pathlen = strlen(path);
  for(size_t i = 0; i < pathlen; i++) {
    out[i] = path[i];
    if(path[i] == '\\')
      out[i] = '/';
  }
}

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-LP]", argv0);
}

int main(int argc, char* argv[]){
  int opt;

  int Lflag = 0;
  int Pflag = 0;

  char cwd[PATH_MAX];
  /*
  if((char* cwd = malloc(PATH_MAX)) == NULL) {
    print_error("%s: malloc failed", argv[0]);
    return -1;
  }
  */

  while((opt = getopt(argc, argv, ":LP")) != -1) {
    switch(opt) {
      case 'L':
        // Use the PWD variable on unix and the CD variable on Windows
        // (logical working directory)
        Lflag = 1;
        break;
      case 'P':
        // Resolve symlinks (aka. "Print physical working directory")
        Pflag = 1; // ignored; default
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  if(!Lflag) {
    // We use OS functions (normal pwd behaviour)
    #ifndef _WIN32 // On Unix
      if(getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
      } else {
        print_error("%s: getcwd() failed", argv[0]);
        return 1;
     }
    #endif

    #ifdef _WIN32
      GetCurrentDirectory(PATH_MAX, cwd);
      if(FORCE_MINGW_PATHS) {
        char* m_cwd = malloc(strlen(cwd));
        mingw_path(m_cwd, cwd);
        printf("%s\n", m_cwd);
      } else {
        printf("%s\n", cwd);
      }
    #endif
  } else {
    // We use PWD/CD environment variable (gnu pwd -L behaviour)
    if(getenv("PWD") != NULL) {
      printf("%s\n", getenv("PWD"));
    } else {
      // TODO: returns null on wine ? To be tested on real Windows
      printf("%s\n", getenv("CD"));
    }
  }

  return 0;
}
