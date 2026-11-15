#ifndef PRETTYPRINT_H
#define PRETTYPRINT_H

#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include "colors.h"

void print_error(const char* format, ...);
void print_warn(const char* format, ...);
void perror2(const char* s, const char* program);

#endif // PRETTYPRINT_H
