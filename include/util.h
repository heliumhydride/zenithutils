#ifndef UTIL_H
#define UTIL_H
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // ssize_t
#include <sys/stat.h> // umask()
#include "../config.h"

char* strsep(char** stringp, const char* delim);
char* getbytes_stdin();
void getline_stdin(char* buf);
ssize_t get_filesize(FILE* fileptr);
int readfile(FILE* fileptr, char* buf);
size_t find_n_of_char_in_str(const char c, const char* str);
int str_is_nan(char* str);
int is_printable_ch(char ch);
void mingw_path(char* out, char* path);
int is_mode_t(char* mode_str);
mode_t get_umask(void);
#endif
