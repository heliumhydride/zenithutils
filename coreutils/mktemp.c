#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include "../include/prettyprint.h"
#include <sodium.h>

#ifdef _WIN32
  #include <windows.h>
#else // On Unix
  #include <sys/stat.h>
#endif

char* xreplacer = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwyz0123456789";

int my_mkdir(const char* pathname, mode_t mode) {
  #ifdef _WIN32
  (void)mode; // Ignore mode parameter
  return mkdir(pathname);
  #else // On Unix
  return mkdir(pathname, mode);
  #endif
}

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-dqu] [-p tmpdir] [-t prefix | template]\n", argv0);
}

char* replace_all_x(char* template) {
  for(int i = 0; i < strlen(template); i++) {
    if(template[i] == 'X') { // if the ith character of template is X
      // replace ith character of template by a random character from 'xreplacer'
      template[i] = xreplacer[randombytes_uniform(strlen(xreplacer))];
    }
  }

  return template;
}

int main(int argc, char* argv[]) {
  if (sodium_init() == -1) {
    print_error("%s: sodium_init() failed", argv[0]);
    return 1;
  }

  int opt;

  int dflag = 0;
  int uflag = 0;
  int qflag = 0;
  int tflag = 0;
  int pflag = 0;

  char* tmpdir;

  #ifdef _WIN32
  tmpdir = getenv("TEMP");
  #else // On Unix
  tmpdir = "/tmp";
  #endif

  char* template;
  char* template_begin = "mktemp";

  while((opt = getopt(argc, argv, ":pt:dqu")) != -1) {
    switch(opt) {
      case 'd': // Create temporary directory instead of a file
        dflag = 1;
        break;
      case 'q': // Quiet mode (fail quietly)
        qflag = 1;
        break;
      case 'u': // Dry run
        uflag = 1;
        break;
      case 't': // do not start name with 'mktemp', instead start with given option
        template_begin = optarg;
        break;
      case 'p': // create temp files in dir
        pflag = 1;
        tmpdir = optarg;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  if(argc == optind) {
    // No argument besides opts, use default template
    // TODO: unsafe ?
    template = malloc(strlen(template_begin) + 9);
    snprintf(template, strlen(template_begin) + 9, "%s.XXXXXXXX", template_begin);
    // ^^^ also unsafe ?
  } else {
    // We have a template provided from argv[optind]
    template = argv[optind];
  }

  char* filename = replace_all_x(template);
  char* fullpath = malloc(strlen(tmpdir) + strlen(filename) + 2);
  snprintf(fullpath, strlen(tmpdir) + strlen(filename) + 2, "%s/%s", tmpdir, filename);

  if(!uflag) {
    if(dflag) { // we create a directory
      if(my_mkdir(fullpath, 0700) != 0) {
        if(!qflag)
          print_error("%s: creating directory '%s' failed", fullpath);
        return 1;
      }
    } else { // we create a file
      // TODO: make permission 0600 (u+rw) on Unix
      FILE *fileptr;
      fileptr = fopen(fullpath, "w");

      if(fileptr == NULL) {
        if(!qflag)
          print_error("%s: creating file '%s' failed", fullpath);
        return 1;
      }

      fclose(fileptr);
    }
  }

  printf("%s\n", filename);
  return 0;
}
