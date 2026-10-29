#include <stdio.h>
#include <libgen.h>

void print_usage(const char* program)
{
  fprintf(stderr, "usage: %s path [...]\n", program);
}

int main(int argc, char* argv[])
{
  if(argc < 2) {
      print_usage(argv[0]);
      return 1;
  }

  while(*++argv)
      printf("%s\n", dirname(*argv));

  return 0;
}
