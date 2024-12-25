#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
//#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
//#include <string.h>
#include <errno.h>

#include "../include/prettyprint.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-pv] dir [dir2] [dir3] ...\n", argv0);
}

int main(int argc, char* argv[]) {
  int opt;
  int pflag = 0; // remove directories recursively
  int vflag = 0; // show operations / verbose mode
  char* program = argv[0];

  while((opt = getopt(argc, argv, ":pv")) != -1) {
    switch(opt) {
      case 'v':
        vflag = 1;
        break;
      case 'p':
        pflag = 1;
        break;
      case '?':
        print_error("%s: option error: unknown option \"-%c\"", program, optopt);
        print_usage(program);
        return 1;
        break;
    }
  }

  if(optind == argc) {
    print_usage(program);
    return 1;
  }
  optind--;

  argv += optind;
  if(!argv[0]) { // no non-option argument is provided
    print_usage(program);
    return 1;
  }

  while(*++argv) {
    // TODO implement rmdir -p
    if(rmdir(*argv) == -1) {
      switch(errno) { // UGLY ERROR HANDLING
        case EACCES:
          print_error("%s: failed to remove '%s': access denied", program, *argv);
          break;
        case EBUSY:
          print_error("%s: failed to remove '%s': device or resource busy", program, *argv);
          break;
        case EINVAL:
          print_error("%s: failed to remove '%s': invalid argument", program, *argv);
          break;
        case ELOOP:
          print_error("%s: failed to remove '%s': too many levels of symlinks", program, *argv);
          break;
        case ENAMETOOLONG:
          print_error("%s: failed to remove '%s': pathname too long", program, *argv);
          break;
        case ENOENT:
          print_error("%s: failed to remove '%s': no such file or directory", program, *argv);
          break;
        case ENOTDIR:
          print_error("%s: failed to remove '%s': not a directory", program, *argv);
          break;
        case ENOTEMPTY:
          print_error("%s: failed to remove '%s': directory not empty", program, *argv);
          break;
        case EPERM:
          print_error("%s: failed to remove '%s': operation not permitted", program, *argv);
          break;
        case EROFS:
          print_error("%s: failed to remove '%s': read-only filesystem", program, *argv);
          break;
        default:
          print_error("%s: failed to remove '%s'", program, *argv);
          break;
      }
      return -1;
    }
    if(vflag)
      printf("%s: removing directory '%s'\n", program, *argv);
  }
  return 0;
}
