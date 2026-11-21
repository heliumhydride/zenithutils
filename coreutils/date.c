#include <stdio.h>            // printf(), fprintf(), putchar()
#include <string.h>           // strcmp()
#include <time.h>             // time(), localtime(), struct tm
#include "../include/util.h"  // shift_args(), print_error()

// TODO [1] shift any arguments using getopt
// TODO     date setting (-s), using utc (-u) pass time argument
// TODO [2] fully document date's fmts in print_usage()
// TODO [3] more complex features like hypens, eg +"%-S" to not pad with zeros
// TODO depending on locale, print hours in 12 hours or 24 hours

// IN VIM:   :r!grep "void print_" %
// and append ';'s at the end
void print_H(const struct tm *t);
void print_M(const struct tm *t);
void print_S(const struct tm *t);
void print_T(const struct tm *t);
void print_Y(const struct tm *t);
void print_d(const struct tm *t);
void print_a(const struct tm *t);
void print_A(const struct tm *t);
void print_b(const struct tm *t);
void print_B(const struct tm *t);
void print_m(const struct tm *t);
void print_F(const struct tm *t);

void process_fmt(char *fmt, const struct tm *t)
{
    // [3]
    // NOTE this functions consumes fmt
    while(*fmt) {
        if(*fmt == '%') {
            ++fmt;
            switch(*fmt) {
                case '%':   putchar('%');    break;
                case 'a':   print_a(t);      break;
                case 'A':   print_A(t);      break;
                case 'b':   print_b(t);      break;
                case 'B':   print_B(t);      break;
                case 'd':   print_d(t);      break;
                case 'F':   print_F(t);      break;
                case 'n':   putchar('\n');   break;
                case 'H':   print_H(t);      break;
                case 'm':   print_m(t);      break;
                case 'M':   print_M(t);      break;
                case 'S':   print_S(t);      break;
                case 't':   putchar('\t');   break;
                case 'T':   print_T(t);      break;
                case 'Y':   print_Y(t);      break;
                default:    printf("%%%c", *fmt);
            }
        } else putchar(*fmt);
        ++fmt;
    }
}

void print_usage(const char *program)
{
    fprintf(stderr, "usage: %s [+format]\n", program);
    // [2]
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

    process_fmt(fmt, t);
    putchar('\n');
    return 0;
}

const char *weekday_names[] = {
    "Sunday", // ...
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

const char *weekday_names_abr[] = {
    "Sun", // ...
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat"
};

const char *month_names[] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

const char *month_names_abr[] = {
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec"
};

void print_H(const struct tm *t)
{
    printf("%02d", t->tm_hour);
}

void print_M(const struct tm *t)
{
    printf("%02d", t->tm_min);
}

void print_S(const struct tm *t)
{
    printf("%02d", t->tm_sec);
}

void print_T(const struct tm *t)
{
    print_H(t);
    putchar(':');
    print_M(t);
    putchar(':');
    print_S(t);
}

void print_Y(const struct tm *t)
{
    printf("%d", t->tm_year + 1900);
}

void print_d(const struct tm *t)
{
    printf("%d", t->tm_mday);
}

void print_a(const struct tm *t)
{
    printf("%s", weekday_names_abr[t->tm_wday]);
}

void print_A(const struct tm *t)
{
    printf("%s", weekday_names[t->tm_wday]);
}

void print_b(const struct tm *t)
{
    printf("%s", month_names_abr[t->tm_mon]);
}

void print_B(const struct tm *t)
{
    printf("%s", month_names[t->tm_mon]);
}

void print_m(const struct tm *t)
{
    printf("%02d", t->tm_mon+1);
}

void print_F(const struct tm *t)
{
    print_Y(t);
    putchar('-');
    print_m(t);
    putchar('-');
    print_d(t);
}
