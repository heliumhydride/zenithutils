#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
//#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
//#include <string.h>

#ifndef _WIN32 // On Unix
#include <fcntl.h>
#include <sys/stat.h>
#include "../include/prettyprint.h"
#include "../include/util.h"
#endif

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-m mode] [-u uid] [-g gid] path b|c|p maj min\n");
}

int main(int argc, char* argv[]){
  #ifdef _WIN32
  fprintf(stderr, "Does not apply to windows\n");
  #endif

  #ifndef _WIN32 // On Unix

  int32_t mode;
  int32_t uid, gid;
  mode = 644; // default mode = rw-r--r--;
  uid  = -1; // -1 means don't set uid
  gid  = -1; // same here, but don't set gid

  // TODO uid, gid segfault (probably at atoi())
  int opt;
  while((opt = getopt(argc, argv, ":m:u:g")) != -1) {
    switch(opt) {
      case 'm': // set mode
        if(str_is_nan(optarg)) {
          printf("%s: invalid mode %s", argv[0], optarg);
          return 1;
        }
        mode = atoi(optarg);
        break;
      case 'u': // set uid
        if(str_is_nan(optarg)) {
          printf("%s: invalid uid %s", argv[0], optarg);
          return 1;
        }
        uid = atoi(optarg);
        break;
      case 'g': // set gid
        if(str_is_nan(optarg)) {
          printf("%s: invalid gid %s", argv[0], optarg);
          return 1;
        }
        gid = atoi(optarg);
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }
  #endif

  printf("mode %u\nuid  %d\ngid  %d\n", mode, uid, gid);

	return 0;
}
