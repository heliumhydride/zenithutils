// Why do *hostname() need this garbage? Can't there just be a '#define _POSIX to handle that?'
#define _DEFAULT_SOURCE
#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <string.h>
#include "../include/prettyprint.h"

#ifdef _WIN32
#include <windows.h>
#else // On Unix
#include <unistd.h>
#endif // _WIN32

#ifdef _WIN32
#undef  gethostname
int gethostname2(char* buf, size_t size) {
  return !GetComputerName(buf, (LPDWORD)&size);
}
#define sethostname(name,size) SetComputerName((name))

#else // On Unix
#define gethostname2 gethostname
#endif // _WIN32

void print_usage(char* program) {
  fprintf(stderr, "usage: %s [new hostname]\n", program);
}

int main(int argc, char* argv[]) {
  if(argc < 2) { // no args, print hostname
    char hostname[512];
    if(gethostname2(hostname, sizeof(hostname)) != 0) {
      print_error("%s: getting hostname failed", argv[0]);
      return 1;
    }
    puts(hostname);
    return 0;
  }
  
  // we have args, check if it's help
  if(!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
    print_usage(argv[0]);
    return 1;
  }

  if(sethostname(argv[1], strlen(argv[1])) == -1) {
    print_error("%s: setting hostname failed, are you root?", argv[0]);
    return 1;
  }

  return 0;
}
