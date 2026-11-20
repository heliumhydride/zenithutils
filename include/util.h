#ifndef UTIL_H
#define UTIL_H
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>    // ssize_t
#include <sys/stat.h>  // umask(), mkdir()
#include <sys/types.h> // mode_t [on linux-glibc platform]
#include "../config.h"

#include "colors.h"
#include <stdarg.h>

ssize_t getdelim(char** lineptr, size_t* n, int delim, FILE* fp);
ssize_t getline(char** lineptr, size_t* n, FILE* fp);
char* strsep(char** stringp, const char* delim);
ssize_t get_filesize(FILE* fileptr);
int str_is_nan(const char* str);
int is_printable_ch(char ch);
void mingw_path(char* out, const char* path);
int is_mode_t(const char* mode_str);
uint16_t reverse_end16(uint16_t val);
uint32_t reverse_end32(uint32_t val);
uint64_t reverse_end64(uint64_t val);
int mkdir2(const char* pathname, const mode_t mode);
void print_error(const char* format, ...);
void print_warn(const char* format, ...);
void perror2(const char* s, const char* program);
void shift_args(int *argcp, char ***argvp);

#endif // UTIL_H
