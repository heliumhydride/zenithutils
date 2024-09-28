#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
//#include <unistd.h>
//#include <string.h>

#include "../include/prettyprint.h"

int main(int argc, char* argv[]){
  // Do we use getopt() or do we use our own parser ? (for -eq, -lt, ...)

  int opt;
  // Not like other opts, [X]flag will increase everytime it is used (so eflag can ==2 for example)
  // zflag != nflag
  int bflag = 0; int cflag = 0; int dflag = 0;
  int eflag = 0; int fflag = 0; int gflag = 0;
  int hflag = 0; int nflag = 0; int pflag = 0;
  int rflag = 0; int sflag = 0; int tflag = 0;
  int uflag = 0; int wflag = 0; int xflag = 0;
  int zflag = 0; int Lflag = 0; int Sflag = 0; 
  if(argc <= 1) {
    return 1;
  } else {
    return 0;
  }
}
