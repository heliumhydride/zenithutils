#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <libgen.h>
#include <string.h>

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s string [suffix]\n", argv0);
}

int main(int argc, char* argv[]){
  if(argc < 2) {
    print_usage(argv[0]);
    return 1;
  }

  size_t off;
  char* p;
  p = basename(argv[1]);
  if((p = basename(argv[1])) == NULL) {
    return 1;
  }

  if (argc >= 3) {
    off = strlen(p) - strlen(argv[2]);
    if (off > 0 && !strcmp(p + off, argv[2]))
      p[off] = '\0';
  }

  printf("%s\n", p);
  return 0;
}
