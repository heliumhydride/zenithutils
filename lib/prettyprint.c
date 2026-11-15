#include "../include/prettyprint.h"
#include "../config.h"

void print_error(const char* format, ...)
{
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

void print_warn(const char* format, ...)
{
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

void perror2(const char* s, const char* program)
{
    #if COLORED_ERRORS
    printf(ANSI_RED);
    fflush(stdout);
    #endif

    if(program != NULL) {
        printf("%s: ", program);
        fflush(stdout);
    }
    perror(s);

    #if COLORED_ERRORS
    printf(ANSI_NORM);
    fflush(stdout);
    #endif
}
