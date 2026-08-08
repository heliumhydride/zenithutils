#ifndef UTIL_H
#define UTIL_H
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // ssize_t
#include <sys/stat.h> // umask()
#include "../config.h"

ssize_t getdelim(char** lineptr, size_t* n, int delim, FILE* fp);
ssize_t getline(char** lineptr, size_t* n, FILE* fp);
char* strsep(char** stringp, const char* delim);
char* getbytes_stdin();
ssize_t get_filesize(FILE* fileptr);
int readfile(FILE* fileptr, char* buf);
int str_is_nan(char* str);
int is_printable_ch(char ch);
void mingw_path(char* out, char* path);
int is_mode_t(char* mode_str);

uint16_t reverse_end16(uint16_t val);
uint32_t reverse_end32(uint32_t val);
uint64_t reverse_end64(uint64_t val);

#endif
