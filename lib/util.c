#define _POSIX_C_SOURCE 200112L

#include "../include/util.h"

char* strsep(char** stringp, const char* delim) {
  char *rv = *stringp;
  if(rv) {
    *stringp += strcspn(*stringp, delim);
    if(**stringp)
      *(*stringp)++ = '\0';
    else
      *stringp = 0;
  }
  return rv;
}

char* fetch_from_stdin() {
  int i = 0;
  // TODO: remove pipe array, and read directly from stdin
  //char pipe[65536];
  char* pipe = malloc(65536);
  while(-1 != (pipe[i++] = getchar()));
    pipe[i-1] = '\0';
  return pipe;
}

size_t find_n_of_char_in_str(const char c, const char* str) {
  size_t count = 0;
  for(int i = 0; i < strlen(str); i++) {
    if(str[i] == c) 
      count++;
  }
  return count;
}

int str_is_nan(char* str) {
  int state = 0;
  for(int i = 0; i < strlen(str); i++) {
    switch(str[i]) {
      case '-': // fallthrough
      case '0': // fallthrough
      case '1': // fallthrough
      case '2': // fallthrough
      case '3': // fallthrough
      case '4': // fallthrough
      case '5': // fallthrough
      case '6': // fallthrough
      case '7': // fallthrough
      case '8': // fallthrough
      case '9':
        break;
      default:
        state = 1;
    }
  }
  return state;
}

void format_time(int* new_time, float time) {
  new_time[0] = (int)floor(time/3600);             // hours
  new_time[1] = (int)floor(fmod(time, 3600) / 60); // minutes
  new_time[2] = (int)floor(fmod(time, 60));        // seconds
}

