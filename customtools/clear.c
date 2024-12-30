#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>

int main(void) {
  // TODO on windows ?
  printf("\033[2J"); // ANSI escape sequence to clear terminal
  printf("\033[H"); // ANSI escape sequence to return to home row
  return 0;
}
