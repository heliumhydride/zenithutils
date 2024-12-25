#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
//#include <stdlib.h>
//#include <getopt.h>
#include <unistd.h>
//#include <string.h>

int main(void) {
  #ifdef _WIN32
  printf("CON\n"); // assume con device on windows
  #else // On Unix
  char* tty_dev = ttyname(STDIN_FILENO);
  if(tty_dev == NULL) {
    printf("not a tty\n");
    return 1;
  }

  printf("%s\n", tty_dev);
  #endif

  return 0;
}
