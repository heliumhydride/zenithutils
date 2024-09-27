#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s time\n", argv0);
}

int main(int argc, char* argv[]){
  double time;
  if(argc <= 1) {
    print_usage(argv[0]);
    return 1;
  }

  time = atof(argv[1]);
  if(time == '\0') {
    print_usage(argv[0]);
    return 1;
  }

  sleep(time);
  return 0;
}
