#define _POSIX_C_SOURCE 200112L

#include "../include/prettyprint.h"

void print_error(const char* format, ...) {
  va_list args;
  fprintf(stderr, "%serror -> ", ANSI_RED);

  va_start(args,format);
  vfprintf(stderr, format, args);
  va_end(args);

  fprintf(stderr, "%s\n", ANSI_NORM);
}

void print_warn(const char* format, ...) {
  va_list args;
  fprintf(stderr, "%swarn -> ", ANSI_YELLOW);

  va_start(args,format);
  vfprintf(stderr, format, args);
  va_end(args);

  fprintf(stderr, "%s\n", ANSI_NORM);
}
