#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
//#include <stdlib.h>
//#include <getopt.h>
//#include <string.h>

#include "../include/prettyprint.h"

int main(int argc, char* argv[]) {
  int qflag = 0;
  int vflag = 0;
  // TODO use realpath(...) on Windows
  // TODO getopt options -q -v -n -f
  if(argc < 2) {
    print_error("%s: path expected\n", argv[0]);
    return 1;
  }

  char buf[1024];
  if(-1 == readlink(argv[1], buf, sizeof(buf))) {
    if(vflag) {
      // TODO error handling
      print_error("%s: '%s': invalid argument", argv[0], argv[1]);
    }
    return 1;
  } else {
    if(!qflag)
      printf("%s\n", buf);
  }
  return 0;
}

