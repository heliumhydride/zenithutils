#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
//#include <stdlib.h>
//#include <getopt.h>
//#include <unistd.h>
//#include <string.h>

#include "../include/prettyprint.h"
#include "../include/util.h"

int main(int argc, char* argv[]){
  char* buf;

  if(argc <= 1) { // No argument
    buf = fetch_from_stdin();
  } else {
    FILE* fileptr;
    fileptr = fopen(argv[1], "r");

    if(NULL == fileptr) {
      print_error("%s: could not open file \"%s\"", argv[0], argv[1]);
      return 1;
    }

    char ch;

    if(fseek(fileptr, 0L, SEEK_END) == 0) {
      size_t filesize = ftell(fileptr);
      if(filesize == -1) {
        print_error("%s: ftell() failed", argv[0]);
        return 1;
      }

      buf = malloc(sizeof(char) * (filesize + 1));

      if(fseek(fileptr, 0L, SEEK_SET) != 0) {
        print_error("%s: fseek() failed", argv[0]);
        return 1;
      }

      size_t newlen = fread(buf, sizeof(char), filesize, fileptr);
      if(ferror(fileptr) != 0) {
        print_error("%s: reading file \"%s\" failed", argv[0], argv[1]);
      } else {
        buf[newlen++] = '\0';
      }
    }

    fclose(fileptr);
  }

  // TODO: print each line in reverse instead of the whole file/stdin in reverse
  for(int i = strlen(buf)-2; i >= 0; i--)
    printf("%c", buf[i]);

  printf("\n");

	return 0;
}
