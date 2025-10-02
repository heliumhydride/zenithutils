#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
//#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "../include/prettyprint.h"
#include "../include/util.h"

int my_mkdir(const char *pathname, mode_t mode, int parent) {
  // TODO implement -p
  (void)parent; // for now, ignore parent
  #ifdef _WIN32
  (void)mode; // forget mode
  return mkdir(pathname);
  #else // On Unix
  return mkdir(pathname, mode);
  #endif
}

void print_usage(const char* argv0) {
  fprintf(stderr, "usage: %s [-m mode] [-pv] dir [dir2] [dir3] ...\n", argv0);
}

int main(int argc, char* argv[]) {
  int opt;
  int pflag = 0; // create directories recursively
  int vflag = 0; // show operations / verbose mode
  int mflag = 0; // using mode flag to set mode
  mode_t mode = 0755;
  #ifndef _WIN32 // On Unix
  mode_t process_umask = 0;
  #endif
  char* program = argv[0];

  while((opt = getopt(argc, argv, ":m:pv")) != -1) {
    switch(opt) {
      case 'v':
        vflag = 1;
        break;
      case 'p':
        pflag = 1;
        break;
      case 'm':
        mflag = 1;
        if(!is_mode_t(optarg)) {
          print_error("%s: invalid mode '%s'", optarg);
          return 1;
        }
        mode = (mode_t)strtol(optarg, NULL, 8);
        #ifndef _WIN32 // On Unix
        process_umask = umask(0);
        #endif
        break;
      case '?': // fallthrough
        print_error("%s: option error: unknown option \"-%c\"", program, optopt);
        print_usage(program);
        return 1;
        break;
      case ':':
        print_error("%s: option \"-%c\" needs an argument", program, optopt);
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
    // TODO implement mkdir -p
    if(my_mkdir(*argv, mode, pflag) == -1) {
      switch(errno) { // UGLY ERROR HANDLING
        case EACCES:
          print_error("%s: cannot create directory '%s': access denied", program, *argv);
          break;
        case EINVAL:
          print_error("%s: cannot create directory '%s': invalid argument", program, *argv);
          break;
        case EMLINK: // fallthrough
        case ELOOP:
          print_error("%s: cannot create directory '%s': too many levels of symlinks", program, *argv);
          break;
        case ENAMETOOLONG:
          print_error("%s: cannot create directory '%s': pathname too long", program, *argv);
          break;
        case ENOENT:
          print_error("%s: cannot create directory '%s': no such file or directory", program, *argv);
          break;
        case ENOTDIR:
          print_error("%s: cannot create directory '%s': not a directory", program, *argv);
          break;
        case EPERM:
          print_error("%s: cannot create directory '%s': operation not permitted", program, *argv);
          break;
        case EROFS:
          print_error("%s: cannot create directory '%s': read-only filesystem", program, *argv);
          break;
        case EBADF:
          print_error("%s: cannot create directory '%s': invalid file descriptor", program, *argv);
          break;
        case EEXIST:
          print_error("%s: cannot create directory '%s': file/directory exists", program, *argv);
          break;
        #ifndef _WIN32 // On Unix
        case EDQUOT: // fallthrough
        #endif
        case ENOSPC:
          print_error("%s: cannot create directory '%s': no space left on device", program, *argv);
          break;
        default:
          print_error("%s: cannot create directory '%s'", program, *argv);
          break;
      }
      return 1;
    }
    if(vflag)
      printf("%s: created directory '%s'\n", program, *argv);
  }

  #ifndef _WIN32 // On Unix
  if(mflag)
    (void)umask(process_umask);
  #endif // _WIN32
  return 0;
}
