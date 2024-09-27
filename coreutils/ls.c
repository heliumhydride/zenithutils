#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <limits.h>

#include "../include/prettyprint.h"
#include "../include/util.h"
#include "../config.h"

#ifdef _WIN32
#include <windows.h>
#endif

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-1AaCFLlhrRst] [path1] ...\n", argv0);
}

int main(int argc, char* argv[]){
  int opt;
  int use_cwd = 0;

  int oneflag = 0;
  int Aflag = 0;
  int aflag = 0;
  int Cflag = 0;
  int Fflag = 0;
  int Lflag = 0;
  int lflag = 0;
  int hflag = 0;
  int rflag = 0;
  int Rflag = 0;
  int sflag = 0;
  int tflag = 0;

  while((opt = getopt(argc, argv, ":1AaCFLlhrRst")) != -1) {
    switch(opt) {
      case '1':
        // 1 column listing
        oneflag = 1;
        break;
      case 'A':
        // List all but '.' and '..'
        Aflag = 1;
        break;
      case 'a':
        // List all
        aflag = 1;
        break;
      case 'C':
        Cflag = 1;
        break;
      case 'F':
        // display '/' after dir; display '*' after executable; display '@' after symlink; display '%' after whiteout (?); display '=' after socket; display '|' after FIFO
        Fflag = 1;
        break;
      case 'L':
        // Evaluate symlinks
        Lflag = 1;
        break;
      case 'l':
        // Long listing mode
        lflag = 1;
        break;
      case 'r':
        // Reverse sort
        rflag = 1;
        break;
      case 'R':
        // Recursive listing
        Rflag = 1;
        break;
      case 's':
        // Sort by size
        sflag = 1;
        break;
      case 't':
        // Sort by date/time modified
        tflag = 1;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  if(optind >=argc)
    use_cwd = 1;

  char cwd[PATH_MAX];

  for(; optind < argc; optind++) {
    printf("path: %s\n", argv[optind]);
  } 

  // if no argument is provided other than parameters, assung current working directory
  #ifndef _WIN32 // on Unix
  if(use_cwd) {
    if(getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("path: %s\n", cwd);
    } else {
      print_error("%s: getcwd() failed", argv[0]);
      return 1;
    }
  }
  
  #endif

  #ifdef _WIN32
  if(use_cwd) {
    GetCurrentDirectory(PATH_MAX, cwd);
    printf("path: %s\n", cwd);
  }
  #endif

  // TODO: get list of files and properties (timestamps, user, group, rwx perms, size, ...)
  // NOTE: maybe spoof some data on Windows ?
  // NOTE: do we use TrustedInstaller Ntauthority/SYSTEM or SYSTEM ?
  // NOTE: when data comes from an unknown uid/gid, go we put the full SID?
  // NOTE: when data comes from another computer, do we specify the computername ? (eg. pc1/core4) ?

  // set to an arbitrary number for now
  // gonna be a problem if we have 4,294,967,295+ files on 32-bit...
  unsigned long nfiles = 1;

  char* filenames[nfiles];
  size_t timestamps[nfiles];
  unsigned int uids[nfiles];
  unsigned int gids[nfiles];
  unsigned short perms[nfiles];

  // TODO: display depending on parameters (-1, -t, -s, -l, -L, -F)
  // lets not try colors yet
  /* char* ls_colors = getenv("LS_COLORS");
  if(ls_colors == NULL)
    ls_colors = "di=";
  */

  return 0;
}
