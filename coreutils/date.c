#include <stdio.h>            // printf(), fprintf(), puts()
#include <string.h>           // strcmp()
#include <time.h>             // time(), localtime(), struct tm, strftime
#include "../include/util.h"  // shift_args(), print_error()

// TODO shift any arguments using getopt
// TODO     date setting (-s), using utc (-u) pass time argument
// TODO [1] fully document date's fmts in print_usage()
// TODO depending on locale, print hours in 12 hours or 24 hours

void print_usage(const char *program)
{
    fprintf(stderr, "usage: %s [+format]\n", program);
    // [1]
    /*
    fprintf(stderr, "\nwhere 'format' can contain the following special sequences\n");
    */
}

int main(int argc, char *argv[])
{
    time_t unixt = time(NULL);
    struct tm *t = localtime(&unixt);

    const char *program = argv[0];
    shift_args(&argc, &argv);

    char *fmt = "%a %b %d %T %Z %Y";
    if(argc > 0) {
        if(strcmp(*argv, "--help") == 0) {
            print_usage(program);
            return 0;
        }

        if(**argv == '+') {
            fmt = *argv;
            ++fmt;
        } else {
            print_error("%s: date format must be passed with a leading '+'\n", program);
            return 1;
        }
    }
    char buf[1024] = {0};
    strftime(buf, sizeof(buf), fmt, t);
    puts(buf);
    return 0;
}

