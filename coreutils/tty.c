#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
//#include <stdlib.h>
//#include <getopt.h>
#include <unistd.h>
//#include <string.h>

int main(int argc, char* argv[]){
  #ifndef _WIN32 // On Unix
  char* tty_dev = ttyname(STDIN_FILENO);
  if(tty_dev == NULL) {
    printf("not a tty\n");
    return 1;
  }

  printf("%s\n", tty_dev);
  return 0;
  #endif

  #ifdef _WIN32
  printf("CON\n"); // assume con device on windows
  #endif
}
