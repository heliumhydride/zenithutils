#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include "../include/util.h"

#undef getdelim // just in case
ssize_t getdelim(char** lineptr, size_t* n, int delim, FILE* fp) {
  if(fp == NULL || n == NULL)
    return -1;

  size_t size = *n;

  char* buf = *lineptr;
  if(buf == NULL) {
    size = 128;
    buf = malloc(size);
    if(buf == NULL)
      return -1;
  }

  size_t len = 0;
  int c;
  while((c = fgetc(fp)) != EOF) {
    if(len + 1 >= size) {
      size += 128;
      char *newptr = realloc(buf, size);
      if(newptr == NULL) {
        free(buf);
        return -1;
      }
      buf = newptr;
    }
    buf[len++] = (char)c;
    if(c == delim)
      break;
  }

  if(len == 0) {
    free(buf);
    return -1;
  }

  buf[len] = '\0';
  *lineptr = buf;
  *n = size;
  return (ssize_t)len;
}

#undef getline
ssize_t getline(char** lineptr, size_t* n, FILE* fp) {
  return getdelim(lineptr, n, (int)'\n', fp);
}

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
  out[pathlen] = '\0';
}

int is_mode_t(char* mode_str) {
  // Conditions: must not be over 3 digits long and must be in positive octal (digits 1 to 7)
  if(strlen(mode_str) >= 3)
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

uint16_t reverse_end16(uint16_t val) {
  return (val << 8) | (val >> 8);
}

uint32_t reverse_end32(uint32_t val) {
  return ((val & 0x000000FF) << 24) |
         ((val & 0x0000FF00) << 8)  |
         ((val & 0x00FF0000) >> 8)  |
         ((val & 0xFF000000) >> 24);
}

uint64_t reverse_end64(uint64_t val) {
  val = ((val << 8) & 0xFF00FF00FF00FF00ULL) | 
        ((val >> 8) & 0x00FF00FF00FF00FFULL);
  val = ((val << 16) & 0xFFFF0000FFFF0000ULL) | 
        ((val >> 16) & 0x0000FFFF0000FFFFULL);
  return (val << 32) | (val >> 32);
}
