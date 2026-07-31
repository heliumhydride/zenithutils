#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include "../include/prettyprint.h"
#include "../config.h"

void print_error(const char* format, ...) {
  va_list args;
  #if COLORED_ERRORS
  fprintf(stderr, "%s", ANSI_RED);
  #endif // COLORED_ERRORS

  va_start(args,format);
  vfprintf(stderr, format, args);
  va_end(args);

  #if COLORED_ERRORS
  fprintf(stderr, "%s", ANSI_NORM);
  #endif // COLORED_ERRORS
  putchar('\n');
}

void print_warn(const char* format, ...) {
  va_list args;
  #if COLORED_ERRORS
  fprintf(stderr, "%swarn -> ", ANSI_YELLOW);
  #endif // COLORED_ERRORS

  va_start(args,format);
  vfprintf(stderr, format, args);
  va_end(args);

  #if COLORED_ERRORS
  fprintf(stderr, "%s", ANSI_NORM);
  #endif // COLORED_ERRORS
  putchar('\n');
}
