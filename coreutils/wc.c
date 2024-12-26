#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
//#include <string.h>

#include "../include/prettyprint.h"
#include "../include/util.h"

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-clmw] [file]\n", argv0);
}

size_t count_lines(const char* str) {
  return find_n_of_char_in_str('\n', str);
}

size_t count_words(const char* str) {
  return find_n_of_char_in_str(' ', str) + count_lines(str);
}

int main(int argc, char* argv[]) {
  int opt;

  char mode = 'a'; // a = all (lines, words, bytes)

  while((opt = getopt(argc, argv, ":clmw")) != -1) {
    switch(opt) {
      case 'c': // fallthrough; count bytes/chars
      case 'l': // fallthrough; count lines (== count linebreaks)
      case 'm': // fallthrough; count characters
      case 'w': //              count words (count spaces+1)
        mode = opt;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  char* input_buffer;

  // Read from stdin if no file
  if(argc == optind) {
    // No file argument
    input_buffer = getbytes_stdin();
    if(NULL == input_buffer) {
      print_error("%s: getbytes_stdin() failed", argv[0]);
      return 1;
    }
  } else {
    // We read from a file
    FILE* fileptr = fopen(argv[optind], "r");
    
    if(NULL == fileptr) {
      print_error("%s: could not open file \"%s\"", argv[0], argv[optind]);
      return 1;
    }

    input_buffer = malloc(get_filesize(fileptr)+1);
    if(readfile(fileptr, input_buffer) == -1) {
      print_error("%s: read error", argv[0]);
    }

    fclose(fileptr);
  }

  switch(mode) {
    case 'a': // count lines, words, bytes
      printf("%6zu", count_lines(input_buffer));
      printf("%6zu", count_words(input_buffer));
      printf("%6zu", strlen(input_buffer));
      if(argc > optind) // If we have a filename as an argument
        printf(" %s", argv[optind]);
      break;
    case 'c': // count bytes
      printf("%zu", strlen(input_buffer));
      if(argc > optind) // If we have a filename as an argument
        printf(" %s", argv[optind]);
      break;
    case 'l': // count lines (= count linebreaks)
      printf("%zu", count_lines(input_buffer));
      if(argc > optind) // If we have a filename as an argument
        printf(" %s", argv[optind]);
      break;
    case 'm': // count characters
      // TODO: for now, same as -c
      printf("%zu", strlen(input_buffer));
      if(argc > optind) // If we have a filename as an argument
        printf(" %s", argv[optind]);
      break;
    case 'w': // count words (= amount of spaces + 1)
      printf("%zu", count_words(input_buffer));
      if(argc > optind) // If we have a filename as an argument
        printf(" %s", argv[optind]);
      break;
    default:
      return 1;
      break;
  }

  printf("\n");
  return 0;
}
