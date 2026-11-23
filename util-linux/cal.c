#include <stdio.h>           // printf(), fprintf(), putchar()
#include <time.h>            // time(), localtime(), mktime(), struct tm
#include <stdlib.h>          // strtol()
#include <string.h>          // strcmp()
#include "../include/util.h" // print_error(), shift_args(), perror2()

/* TODO specify date from argv
   TODO flags
            allow starting with monday -m flag
            -1, -s flag, does nothing
            -n flag
            -3 [== '-n 3']
            -v, vertical calendar (ncal(1) mode)
   TODO center output [1]
   TODO default to monday or sunday as start depending on locale
*/

#define WEEK 7 // days
#define CAL_WIDTH 20 // output is 20 chars wide for a single 'cal' cmd

const char *month_names[] = {
    "January",   "February", "March",    "April",
    "May",       "June",     "July",     "August",
    "September", "October",  "November", "December"
};

const char *weekday_names[WEEK] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};

#define out_if_invalid_year() \
    if(*argv == endptr) {     \
        fprintf(stderr, "%s: invalid year '%s'\n", program, *argv); \
        return 1;             \
    }

void print_usage(const char *program)
{
    fprintf(stderr, "usage: %s [-n months] [-13sv] [[[day] month] year]\n", program);
}

int main(int argc, char* argv[])
{
    const char *program = *argv;
    shift_args(&argc, &argv);
    struct tm tm = {0};

    if(argc >= 1) {
        if(!strcmp(*argv, "--help")) {
            print_usage(program);
            return 0;
        }
        // TODO check year and day intervals
        char *endptr;
        int y,m,d;
        switch(argc) {
            case 1:
                d = 1;
                m = 1;
                y = (int)strtol(*argv, &endptr, 10);
                out_if_invalid_year()
                break;
            case 2:
                // note: we can do atoi because m is never going to be zero anyways
                d = 1;
                m = atoi(*argv++);
                y = (int)strtol(*argv++, &endptr, 10);
                out_if_invalid_year();
                break;
            case 3:
                d = atoi(*argv++);
                m = atoi(*argv++);
                y = (int)strtol(*argv++, &endptr, 10);
                out_if_invalid_year()
                break;
            default:
                print_error("%s: too many arguments", program);
                return 1;
        }
        // TODO day correctness depends on month (and year for February)
        if(d <= 0 || d > 31) {
            print_error("%s: invalid day", program);
            return 1;
        }
        if(m <= 0 || m > 12) {
            print_error("%s: invalid month", program);
            return 1;
        }

        tm.tm_year = y - 1900;
        tm.tm_mon  = m - 1;
        tm.tm_mday = d;
        mktime(&tm);
        if(tm.tm_wday == -1) {
            perror2("mktime() failed", program);
            return 1;
        }
    } else {
        time_t unixt = time(0);
        tm = *localtime(&unixt);
    }

    // [1]
    printf("%*s %04d\n", CAL_WIDTH-8, month_names[tm.tm_mon], tm.tm_year+1900);
    for(size_t i = 0; i < 7; ++i)
        printf("%s ", weekday_names[i]);
    putchar('\n');

    struct tm firstofmonth = {0};
    firstofmonth.tm_year = tm.tm_year;
    firstofmonth.tm_mon  = tm.tm_mon;
    firstofmonth.tm_mday = 1;

    mktime(&firstofmonth);
    if(firstofmonth.tm_wday == -1) {
        perror2("mktime() failed", program);
        return 1;
    }

    int first_day_of_week = firstofmonth.tm_wday;
    if(first_day_of_week > 0)
        printf("%*s", firstofmonth.tm_wday*3, " "); // print two spaces instead of a %02d int

    for(; firstofmonth.tm_mday < 31; ++firstofmonth.tm_mday) { // TODO < 28, 29, 30 [maxmonths(tm.tm_mon);]
        if(firstofmonth.tm_mday == tm.tm_mday)
            printf("\033[7m"); // TODO don't highlight if no day speicifed
        printf("%2d", firstofmonth.tm_mday);

        if(firstofmonth.tm_mday == tm.tm_mday)
            printf("\033[0m ");
        else
            putchar(' ');

        if(((firstofmonth.tm_mday + first_day_of_week) % 7) == 0)
            putchar('\n');
    }
    putchar('\n');
    return 0;
}
