#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
//#include <string.h>

#include "../include/prettyprint.h"
#include "../include/util.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-nfo] [-t o|d|x] file [files ...]\n", argv0);
}

int main(int argc, char* argv[]) {
  int opt;

  int tflag = 0;
  char* tmode;
  int fflag = 0;

  // TODO: Getopt options
  while((opt = getopt(argc, argv, ":nt:fo")) != -1) {
    switch(opt) {
      case 'n':
        break;
      case 't':
        tflag = 1;
        tmode = optarg;
        if(tmode == NULL) {
          print_error("%s option '-t' requires an argument", argv[0]);
          return 1;
        }
        break;
      case 'f':
        fflag = 1;
        break;
      case 'o':
        tflag = 1;
        tmode = "o";
        break;
      case '?':
        print_error("%s: invalid option -- '%c'\n", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  if(argc==optind) { // no file arg provided
    print_usage(argv[0]);
    return 1;
  }

  FILE* fileptr = fopen(argv[optind], "r");

  if(NULL == fileptr) {
    print_error("%s: could not open file \"%s\"", argv[0], argv[optind]);
    return 1;
  }

  size_t filesize = get_filesize(fileptr);

  char* buf = malloc(filesize);
  if(readfile(fileptr, buf) == -1) {
    print_error("%s: read error", argv[0]);
  }

  fclose(fileptr);

  // TODO: Split each string, not characters (to put filename before each line/string via -f option)
  char* tmp_str;
  char* str_ptr = tmp_str;
  char ch; char* chptr = &ch;
  for(int i = 0; i < filesize; i++) {
    ch = buf[i];
    if(is_printable_ch(ch))
      printf("%c", *chptr);
    /*
    while(*chptr++ != '\0' || *chptr != '\n') { // strings will be separated by NULL or LF
      if(is_printable_ch(*chptr))
        *str_ptr++ = *chptr;
    }
    *str_ptr-- = '\0'; // terminate string
    if(fflag)
      printf("%s: ", argv[optind]);
    printf("%s\n", tmp_str);
    str_ptr = tmp_str; // reset string pointer to be able to repeat the loop
    */
  }

  free(buf);
  return 0;
}
