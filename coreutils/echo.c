#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>

// TODO echo -e
// TODO echo -n
int main(int argc, char* argv[]) {
  if(argc < 2)
    return 0;
  while(*++argv) {
    printf("%s ", *argv);
  }
  putchar('\n');
  return 0;
}
