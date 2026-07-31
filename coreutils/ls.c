#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <dirent.h>
//#include <getopt.h>
#include "../config.h"

#define DT_UNKNOWN 0
#define DT_FIFO 1
#define DT_CHR 2
#define DT_DIR 4
#define DT_BLK 6
#define DT_REG 8
#define DT_LNK 10
#define DT_SOCK 12
#define DT_WHT 14

// TODO allow file as argument
// TODO options
// TODO formatting

int main(int argc, char* argv[]) {
  char* program = argv[0];
  char* path = ".";
  if(argc >= 2) {
    path = argv[1];
  }

  DIR* d = opendir(path);
  if(d == NULL) {
    fprintf(stderr, "%s: %s :no such file or directory\n", program, path);
    return 1;
  }

  struct dirent* ent;
  while((ent = readdir(d))) {
    #ifdef LS_COLOR
    #ifndef _WIN32 // TODO
    switch(ent->d_type) {
      case DT_BLK: // fallthrough
      case DT_CHR: // bright yellow
        printf("\033[1;33m");
        break;
      case DT_DIR:
        printf("\033[1;34m");
        break;
      case DT_FIFO:
      case DT_SOCK:
        printf("\033[1;35m");
        break;
      case DT_LNK:
        printf("\033[1;36m");
        break;
    }
    #endif // _WIN32
    #endif // LS_COLOR

    printf("%s ", ent->d_name);

    #ifdef LS_COLOR
    #ifndef _WIN32
    printf("\033[0m");
    #endif // _WIN32
    #endif // LS_COLOR
  }

  putchar('\n');
  return 0;
}
