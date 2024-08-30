#ifndef UTIL_H
#define UTIL_H
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

char* strsep(char** stringp, const char* delim);
char* fetch_from_stdin();
size_t find_n_of_char_in_str(const char c, const char* str);
char* base64_encode(char* str);
char* base64_decode(char* str);
int str_is_nan(char* str);

#endif
