#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include "../include/util.h"

// TODO rm -r, -i
// TODO properly make use of -f flag ?

void print_usage(const char* program)
{
  fprintf(stderr, "usage: %s [-fiRrv] file [...]\n", program);
}

int main(int argc, char* argv[])
{
  const char* program = argv[0];

  int vflag = 0;
  int fflag = 0;

  int opt;
  while((opt = getopt(argc, argv, ":fiRrv")) != -1) {
      switch(opt) {
          case 'v':
              vflag = 1;
              break;
          case 'f':
              fflag = 1;
              break;
          case '?':
              print_error("%s: unknown option '-%c'", program, optopt);
              print_usage(program);
              return 1;
              break;
      }
  }
  
  argc -= optind;
  argv += optind - 1;

  if(argc == 0) {
      print_usage(program);
      return 1;
  }

  while(*++argv) {
      int res = unlink(*argv);
      if(res == -1) {
          if(!fflag) {
              print_error("%s: could not remove '%s'", program, *argv);
              return 1;
          }
      } else {
          if(vflag)
              printf("removed '%s'\n", *argv);
      }
  }

  return 0;
}
