#ifndef PRETTYPRINT_H
#define PRETTYPRINT_H
#include <stdarg.h>
#include <stdio.h>
#include "colors.h"

void print_error(const char* format, ...);
void print_warn(const char* format, ...);

#endif
