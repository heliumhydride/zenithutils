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
  fprintf(stderr, "usage: %s [-m mode] [-u uid] [-g gid] path type maj [min]\n", argv0);
  fprintf(stderr, "       where type is b|c/u|p\n");
}

int main(int argc, char* argv[]){
  #ifdef _WIN32
  fprintf(stderr, "Does not apply to windows\n");
  return 1;
  #endif

  #ifndef _WIN32 // On Unix

  uint32_t mode = 644; // default mode = rw-r--r--;
  int32_t uid, gid;
  uid = gid = -1; // -1 means default (u/g)id for user
  
  char*    filename;
  char     type;
  uint32_t maj = 0;
  uint32_t min = 0;

  // TODO uid, gid segfault (probably at atoi())
  int opt;
  while((opt = getopt(argc, argv, ":m:u:g:")) != -1) {
    switch(opt) {
      case 'm': // set mode
        if(str_is_nan(optarg)) {
          print_error("%s: invalid mode \"%s\": not a number", argv[0], optarg);
          print_usage(argv[0]);
          return 1;
        }
        mode = atoi(optarg);
        break;
      case 'u': // set uid
        if(str_is_nan(optarg)) {
          print_error("%s: invalid uid \"%s\": not a number", argv[0], optarg);
          print_usage(argv[0]);
          return 1;
        }
        uid = atoi(optarg);
        break;
      case 'g': // set gid
        if(str_is_nan(optarg)) {
          print_error("%s: invalid gid \"%s\": not a number", argv[0], optarg);
          print_usage(argv[0]);
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

  printf("mode %u\nuid  %d\ngid  %d\n", mode, uid, gid);
  /*
  for(; optind<argc; optind++) {
    printf("%s    %d\n", argv[optind], optind);
  }
  */
  printf("%s %s %s %s\n", argv[optind], argv[optind+1], argv[optind+2], argv[optind+3]);

  filename = argv[optind];
  type     = argv[optind+1][0];
  maj      = atoi(argv[optind+2]);
  maj      = atoi(argv[optind+3]);

  if(argv[optind] == NULL) {
    print_error("%s: no node filename specified", argv[0]);
    return 1;
  }

  if(argv[optind+1] == NULL) {
    print_error("%s: specify node type", argv[0]);
    return 1;
  }

  if(argv[optind+2] == 0) {
    print_error("%s: invalid node maj", argv[0]);
  }

	return 0;
  #endif
}
