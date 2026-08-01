#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>

int main(void) {
  FILE* fp = fopen("/etc/nologin.txt", "r");
  if(fp == NULL) {
    printf("This account is currently not available.\n");
    return 1;
  }
  int c;
  while((c = fgetc(fp)) != EOF)
    putchar(c);
  return 1;
}
