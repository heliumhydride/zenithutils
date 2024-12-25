#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>

#include "../include/prettyprint.h"
#include "../include/util.h"

// all of the variables below need to be defined globally for is_there() and print_matches() to access
static int sflag;
static int aflag;
//static int status;

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-as] program ...\n", argv0);
}

int is_there(char* candidate) {
  char* new_candidate;

  #ifdef _WIN32
  if(FORCE_MINGW_PATHS) {
    new_candidate = malloc(strlen(candidate) + 1);
    mingw_path(new_candidate, candidate);
  } else {
    new_candidate = candidate;
  }
  #endif

  #ifndef _WIN32 // On Unix
  new_candidate = candidate;
  #endif

  if(!access(candidate, X_OK)) {
    if(!sflag){
      printf("%s\n", new_candidate);
    }
    return 1;
  }
  return 0;
}

int print_matches(char* path, char* filename) {
  char candidate[PATH_MAX];
  const char* d;
  int found;

  if (strchr(filename, '/') != NULL)
    return (is_there(filename) ? 0 : -1);
  found = 0;
  // TODO: if compiling for Windows, accept both ':' and ';' as separator, but not mixed
  // TODO: check in current directory on Windows
  #ifndef _WIN32 // On Unix
  char* path_env_sep = ":";
  #endif
  #ifdef _WIN32
  char* path_env_sep = ";";
  #endif
  while((d = strsep(&path, path_env_sep)) != NULL) {
	  if (*d == '\0')
      d = ".";
    char dir_sep = '/';
    #ifdef _WIN32
    dir_sep = '\\';
    #endif
    if(snprintf(candidate, sizeof(candidate), "%s%c%s", d, dir_sep, filename) >= (int)sizeof(candidate))
      continue;
    if(is_there(candidate)) {
      found = 1;
      if(!aflag)
        break;
    } else {
      strcat(candidate, ".exe");
      if(is_there(candidate)) {
        found = 1;
        if(!aflag)
          break;
      }
    }
 	}
  return (found ? 0 : -1);
}

int main(int argc, char* argv[]) {
  int opt;

  size_t pathlen;
  char* p, *path;

  sflag = 0;
  aflag = 0;
  //status = 0;

  while((opt = getopt(argc, argv, ":as")) != -1) {
    switch(opt) {
      case 'a':
        // enable all paths, not just the first one
        aflag = 1;
        break;
      case 's':
        // silent which (no output, only exit code)
        sflag = 1;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }


  if(argc < 2) {
    print_usage(argv[0]);
    return 1;
  }
  
  if((p = getenv("PATH")) == NULL) {
    if(!sflag)
      print_error("%s: environment variable PATH not defined", argv[0]);
    return 1;
  }

  pathlen = strlen(p) + 1;
	path = malloc(pathlen);
  if(path == NULL) {
    print_error("%s: malloc failed ?");
    return 2;
  }

  //int optind_orig = optind; // just in case for future use
  for(; optind < argc; optind++) {
    memcpy(path, p, pathlen);
    if(print_matches(path, argv[optind]) == -1)
      return 1;
  }

  return 0;
}
