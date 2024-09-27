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
  return find_n_of_char_in_str(' ', str) + 1;
}

int main(int argc, char* argv[]){
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

  char* stdin_buffer;

  // Read from stdin if no file
  if(argc == optind) {
    // No file argument
    stdin_buffer = fetch_from_stdin();
    if(NULL == stdin_buffer) {
      print_error("%s: fetch_from_stdin() failed", argv[0]);
      return 1;
    }
  } else {
    // We read from a file
    FILE* fileptr;
    fileptr = fopen(argv[optind], "r");
    
    if(NULL == fileptr) {
      print_error("%s: could not open file \"%s\"", argv[0], argv[optind]);
      return 1;
    }

    char ch;

    if(fseek(fileptr, 0L, SEEK_END) == 0) {
      size_t filesize = ftell(fileptr);
      if(filesize == -1) {
        print_error("%s: ftell() failed", argv[0]);
        return 1;
      }

      stdin_buffer = malloc(sizeof(char) * (filesize + 1));

      if(fseek(fileptr, 0L, SEEK_SET) != 0) {
        print_error("%s: fseek() failed", argv[0]);
        return 1;
      }

      size_t newlen = fread(stdin_buffer, sizeof(char), filesize, fileptr);
      if(ferror(fileptr) != 0) {
        print_error("%s: reading file \"%s\" failed", argv[0], argv[optind]);
      } else {
        stdin_buffer[newlen++] = '\0';
      }

    }

    fclose(fileptr);
  }

  switch(mode) {
    case 'a': // count lines, words, bytes
      printf("%6u", count_lines(stdin_buffer));
      printf("%6u", count_words(stdin_buffer));
      printf("%6u", strlen(stdin_buffer));
      if(argc > optind) // If we have a filename as an argument
        printf(" %s", argv[optind]);
      break;
    case 'c': // count bytes
      printf("%d\n", strlen(stdin_buffer));
      if(argc > optind) // If we have a filename as an argument
        printf(" %s", argv[optind]);
      break;
    case 'l': // count lines (= count linebreaks)
      printf("%u", count_lines(stdin_buffer));
      if(argc > optind) // If we have a filename as an argument
        printf(" %s", argv[optind]);
      break;
    case 'm': // count characters
      // TODO: for now, same as -c
      printf("%u", strlen(stdin_buffer));
      if(argc > optind) // If we have a filename as an argument
        printf(" %s", argv[optind]);
      break;
    case 'w': // count words (= amount of spaces + 1)
      printf("%u", count_words(stdin_buffer));
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
