#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
//#include <getopt.h>
//#include <unistd.h>

void print_usage(char* program) {
  fprintf(stderr, "usage: %s pid\n", program);
}

// TODO support process names ?
// TODO support passing signal as parameter

int main(int argc, char* argv[]) {
  if(argc <= 1) {
    print_usage(argv[0]);
    return 1;
  }

  pid_t pid = (int)atoi(argv[1]);
  int sig = SIGTERM;

  if(pid == 0) {
    if(strcmp(argv[1], "0")) {
      fprintf(stderr, "%s: '%s': not a number\n", argv[0], argv[1]);
      return 1;
    } else {
      fprintf(stderr, "%s: cannot kill pid 0\n", argv[0]);
      return 1;
    }
  }

  if(kill(pid, sig) == -1) {
    fprintf(stderr, "%s: killing process of PID %s failed\n", argv[0], argv[1]);
  }
  return 0;
}
