#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
//#include <stdlib.h>
//#include <string.h>

#include "../include/prettyprint.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-cdu] [infile [outfile]]", argv0);
}

int main(int argc, char* argv[]){
  int opt;
  int cflag = 0;
  int dflag = 0;
  int uflag = 0;

  while((opt = getopt(argc, argv, ":cdu")) != -1) {
    switch(opt) {
      case 'c':
        cflag = 1;
        break;
      case 'd':
        dflag = 1;
        break;
      case 'u':
        uflag = 1;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  // TODO check for stdin input or filename
  // TODO load file into buffer
  // TODO split into each line
  // TODO go through each line and either show only duplicates or unique lines

	return 0;
}
