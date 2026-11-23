#ifndef UTIL_H
#define UTIL_H
#include <string.h>    // strlen()
#include <stdint.h>    // uint*_t
#include <stdlib.h>    // strtol(), realloc(), free(), abort()
#include <stdio.h>     // fprintf(), printf()
#include <unistd.h>    // ssize_t
#include <sys/stat.h>  // umask(), mkdir()
#include <sys/types.h> // mode_t [on linux-glibc platform]
#include <stdarg.h>    // va_list, va_start, va_end

#ifdef _WIN32
#include <process.h>   // _spawnvp();
#else
#include <sys/wait.h>  // waitpid(), WIFEXITED, WEXITSTATUS
#endif

#include "../config.h" // COLORED_ERRORS
#include "colors.h"    // ANSI_*

/*
    Typedefs and defines
*/

#define LIBUTIL_NAME "zenithutils libutil"

typedef struct {
    char   **data;
    size_t count;
    size_t capacity;
} cmd_t;

/*
    Prototypes for util.c
*/

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
void shift_args_n(int *argcp, char ***argvp, const int n);
int str_startwith(const char *s, const char *prefix);
int str_endswith(const char *s, const char *suffix);
int cmd_run(cmd_t *cmd);

/*
    Function macros
*/

#define __TODO(msg)   do { fprintf(stderr, "%s: %d: \033[7;33mTODO\033[0m   %s\n", __FILE__, __LINE__, (msg)); abort(); } while(0)

#define da_reserve_memory(da, size)                                                 \
    do {                                                                            \
        if((size) > (da)->capacity) {                                               \
            if((da)->capacity == 0) (da)->capacity = 1;                             \
            while((size) > (da)->capacity)  (da)->capacity *= 2;                    \
            (da)->data = realloc((da)->data, (da)->capacity * sizeof(*(da)->data)); \
            if((da)->data == NULL) perror2("malloc", NULL);                         \
        }                                                                           \
    } while(0)

#define da_append(da, x)                                \
    do {                                                \
        da_reserve_memory((da), (da)->count+1);         \
        (da)->data[(da)->count++] = (x);                \
    } while(0)

#define da_pop(da)  if((da)->count > 0) (da)->count--

#define da_insert(da, x, pos)                           \
    do {                                                \
        da_reserve_memory((da), (da)->count+1);         \
        for(size_t i = (da)->count; i > (pos); --i)     \
            (da)->data[i] = (da)->data[i-1];            \
        (da)->data[(pos)] = (x);                        \
        (da)->count++;                                  \
    } while(0)

#define da_delete(da, pos)                              \
    do {                                                \
        for(size_t i = (da)->count - 1; i > (pos); --i) \
            (da)->data[i-1] = (da)->data[i];            \
        --(da)->count;                                  \
    } while(0)

#define da_destroy(da)       \
    do {                     \
        free((da)->data);    \
        (da)->count = 0;     \
        (da)->capacity = 0;  \
        (da)->data = NULL;   \
    } while(0)

// could have used 'typeof(*(da)->data)' but typeof is since C23
#define da_reverse(da, type)                               \
    do {                                                   \
        for(size_t i = 0; i < (da)->count/2; ++i) {        \
            type tmp = (da)->data[i];                      \
            (da)->data[i] = (da)->data[(da)->count - i-1]; \
            (da)->data[(da)->count - i-1] = tmp;           \
        }                                                  \
    } while(0)
/*
    I   ┌───────────┐   II     ┌─────┐     III
        1  2  3  4  5       5  2  3  4  1      5  4  3  2  1
*/

#endif // UTIL_H
