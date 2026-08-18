#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifndef _WIN32 // On Unix
#include <sys/wait.h>
#endif // !_WIN32

#define STB_DS_IMPLEMENTATION
#include "../include/stb_ds.h"

#include "../include/prettyprint.h"
#include "../config.h"

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
  argv++;

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

  // start building new argv from the program's one (after the program path)
  char** new_argv = NULL;
  stbds_arrput(new_argv, path);
  while(*++argv)
    stbds_arrput(new_argv, *argv);

  // build the rest of new argv from buffer (stdin)
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
  }
  stbds_arrput(new_argv, NULL);

  int res = 126;
#ifdef _WIN32
  res = execvp(path, new_argv);
#else // On Unix
  int wstatus;
  pid_t pid = fork();
  switch(pid) {
    case -1:
      print_error("%s: could not fork()", program);
      return 2;
    case 0:
      res = execvp(path, new_argv);
      break;
    default:
      (void)waitpid(pid, &wstatus, 0);
      if(WIFEXITED(wstatus))
        res = WEXITSTATUS(wstatus);
      break;
  }
#endif // _WIN32

  free(buf);
  stbds_arrfree(new_argv);
  return res;
}

