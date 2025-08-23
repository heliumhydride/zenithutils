#define _XOPEN_SOURCE   600
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

char* getbytes_stdin() {
  int i = 0;
  char* pipe = malloc(STDIN_MAX);
  while(-1 != (pipe[i++] = getchar()));
    pipe[i-1] = '\0';
  return pipe;
}

void getline_stdin(char* buf) {
  // TODO multiline stdin ?
  fgets(buf, STDIN_MAX, stdin);
}

ssize_t get_filesize(FILE* fileptr) {
  if(fileptr == stdin)
    return -1;
  ssize_t filesize;
  if(fseek(fileptr, 0L, SEEK_END) != 0)
    return -1;
  if((filesize = ftell(fileptr)) == -1)
    return -1;
  if(fseek(fileptr, 0L, SEEK_SET) != 0)
    return -1;
  return filesize;
}

int readfile(FILE* fileptr, char* buf) {
  ssize_t filesize = get_filesize(fileptr);
  if(filesize == -1)
    return -1;

  size_t bytes_read = fread(buf, sizeof(char), filesize, fileptr);
  if(ferror(fileptr) != 0) {
    return -1;
  }

  buf[bytes_read++] = '\0'; // terminate buffer string
  return 0;
}

size_t find_n_of_char_in_str(const char c, const char* str) {
  size_t count = 0;
  for(size_t i = 0; i <= strlen(str); i++) {
    if(str[i] == c) 
      count++;
  }
  return count;
}

int str_is_nan(char* str) {
  int state = 0;
  for(size_t i = 0; i < strlen(str); i++) {
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

int is_printable_ch(char c) {
  /*
    Alternative portable isprint(char c) (ASCII ONLY)
    Will return 1 if character is printable, 0 if it is not
  */
  // TODO Unicode ?

  /* 
    if(c == '\n')
      return 1;
  */
  /*
    if(c == '\r')
      return 1;
  */
  if(c >= 32 && c <= 126) // From Space to ~
    return 1;
  // if checks fail return 0
  return 0;
}

void mingw_path(char* out, char* path) {
  size_t pathlen = strlen(path);
  for(size_t i = 0; i < pathlen; i++) {
    out[i] = path[i];
    if(path[i] == '\\')
      out[i] = '/';
  }
}

int is_mode_t(char* mode_str) {
  // Conditions: must not be over 3 digits long and must be in positive octal (digits 1 to 7)
  if(strlen(mode_str) > 3)
    return 1;
  int state = 0;
  for(size_t i = 0; i < strlen(mode_str); i++) {
    switch(mode_str[i]) {
      case '0': // fallthrough
      case '1': // fallthrough
      case '2': // fallthrough
      case '3': // fallthrough
      case '4': // fallthrough
      case '5': // fallthrough
      case '6': // fallthrough
      case '7': // fallthrough
        break;
      default:
        state = 1;
    }
  }
  return state;
}
