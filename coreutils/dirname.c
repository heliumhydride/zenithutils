#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <libgen.h>

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s path\n", argv0);
}

int main(int argc, char* argv[]){
  if(argc < 2) {
    print_usage(argv[0]);
    return 1;
  }

  printf("%s\n", dirname(argv[1]));
	return 0;
}
