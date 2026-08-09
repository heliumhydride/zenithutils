#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STB_DS_IMPLEMENTATION
#include "../include/stb_ds.h"

#include "../include/prettyprint.h"
#include "../config.h"

// TODO [1] fork on Unix
// TODO build from existing argv too, allow for other args basically
// TODO -0 option

void print_usage(char* program) {
  fprintf(stderr, "usage: %s command\n", program);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];
  if(argc < 2) {
    print_usage(program);
    return 1;
  }
  char* path = argv[1];

  char* buf = malloc(STDIN_MAX);
  if(buf == NULL) {
    print_error("%s: malloc() failed", program);
    return 2;
  }
  int c;
  int i = 0;
  while((c = getchar()) != EOF) {
    buf[i] = (char)c;
    i++;
  }
  buf[i] = '\0';

  char** new_argv;
  int new_argc = 1;
  stbds_arrput(new_argv, path);

  const char* separators = " \n\t";
  char* pch = strtok(buf, separators);
  while(pch != NULL) {
    char* pch2 = malloc(strlen(pch) + 1);
    if(pch2 == NULL) {
      print_error("%s: malloc() failed", program);
      return 2;
    }
    strcpy(pch2, pch);
    stbds_arrput(new_argv, pch2);
    pch = strtok(NULL, separators);
    new_argc++;
  }
  stbds_arrput(new_argv, NULL);

  // TODO [1]
  int res = execvp(path, new_argv);
  // NOTE on Windows, this won't be a problem because mingw's execvp uses CreateProcess instead of replacing the process (like a normal exec should?)

  // these two will never happen until [1] is fixed
  free(buf);
  return res;
}

