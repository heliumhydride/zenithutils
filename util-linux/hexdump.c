#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include "../include/prettyprint.h"

// TODO last ascii representation not being printed at the end
// TODO options

void print_ascii_representation(const uint8_t* buf) {
  printf(" |");
  for(size_t i = 0; i < 0x10; i++) {
    if(buf[i] == '\0') break;
    putchar(isprint(buf[i]) ? buf[i] : '.');
  }
  putchar('|');
}

void print_usage(char* program) {
  fprintf(stderr, "usage: %s file\n", program);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];
  if(argc < 2) {
    print_usage(program);
    return 1;
  }

  argv++;
  FILE* fp = fopen(*argv, "rb");
  if(fp == NULL) {
    print_error("%s: %s: could not open file", program, *argv);
    return 1;
  }

  uint8_t buf[0x10] = {0};
  size_t addr = 0x00;
  int c;
  while((c = fgetc(fp)) != EOF) {
    if((addr % 0x10) == 0) printf("%08zx  ", addr);
    if((addr % 0x10) == 0x08) putchar(' ');

    printf("%02x ", (uint8_t)c);
    buf[addr % 0x10] = (uint8_t)c;

    if((++addr % 0x10) == 0) {
      print_ascii_representation(buf);
      putchar('\n');
    }
  }
  if((addr % 0x10) > 0) putchar('\n');
  printf("%08zx\n", addr);

  fclose(fp);
  return 0;
}

