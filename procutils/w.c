#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
//#include <stdlib.h>
//#include <getopt.h>
#include <unistd.h>
//#include <string.h>

#include "../include/prettyprint.h"
#include "../config.h"

#ifdef _WIN32
#include <windows.h>
#endif

#ifndef _WIN32 // On Unix
#endif

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-ps]\n", argv0);
}

void print_version() {
  fprintf(stderr, "uptime from zenithutils " VERSION "\n");
}

int main(int argc, char* argv[]){
  int opt;
  int pflag = 0;
  int sflag = 0;

  while((opt = getopt(argc, argv, ":psV")) != -1) {
    switch(opt) {
      case 'p':
        pflag = 1;
        break;
      case 's':
        sflag = 1;
        break;
      case 'V': // compat with standard uptime -V
        print_version();
        return 1;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  if(pflag == 1) {
    printf("execute uptime -p\n");
  } else if(sflag == 1){
    printf("execute uptime -s\n");
  } else {
    printf("execute default uptime behaviour\n");
  }

  #ifndef _WIN32 // On Unix
  #endif

  #ifdef _WIN32
  #endif
	return 0;
}
