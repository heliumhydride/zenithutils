#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
//#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <time.h>
#include <math.h>
#include <stdint.h>

#include "../include/prettyprint.h"
#include "../config.h"

#ifdef _WIN32
#include <windows.h>
#endif

#ifndef _WIN32 // On Unix
#include <utmp.h>
#endif

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-ps]\n", argv0);
}

void print_version() {
  fprintf(stderr, "w/uptime from zenithutils " VERSION "\n");
}

int main(int argc, char* argv[]){
  int uptime_mode = 0;
  int opt;

  // flags for uptime: -psV
  // flags for w     : -AhiMNpns
  int uptime_pflag = 0;
  int uptime_sflag = 0;
  int pflag = 0;
  int sflag = 0;

  int hflag = 0;
  int Aflag = 0;
  int iflag = 0;
  int Mflag = 0;
  int Nflag = 0;
  int nflag = 0;

  if(basename(argv[0])[0] == 'u') {
    uptime_mode = 1;
  }

  while((opt = getopt(argc, argv, ":psVhAiMNn")) != -1) {
    switch(opt) {
      case 'p':
        if(uptime_mode) {
          uptime_pflag = 1;
        } else {
          pflag = 1;
        }
        break;
      case 's':
        if(uptime_mode) {
          uptime_sflag = 1;
        } else {
          sflag = 1;
        }
        break;
      case 'h':
        hflag = 1;
        break;
      case 'A':
        Aflag = 1;
        break;
      case 'i':
        iflag = 1;
        break;
      case 'M':
        Mflag = 1;
        break;
      case 'N':
        Nflag = 1;
        break;
      case 'n':
        nflag = 1;
        break;
      case 'V': // compat with standard uptime -V
        print_version();
        return 1;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  #ifndef _WIN32 // On Unix
    if(!hflag) {
      /*
         gather some data
      */
      // should we read /proc/uptime or not ?
      FILE* uptime_file; // /proc/uptime
      double uptime; // uptime in seconds
      uptime_file = fopen("/proc/uptime", "r");

      if(uptime_file == NULL) {
        print_error("could not open /proc/uptime");
        return 1;
      }

      fscanf(uptime_file, "%lf", &uptime);
      fclose(uptime_file);
      
      time_t rawtime;
      struct tm* timeinfo;

      time(&rawtime);
      timeinfo = localtime (&rawtime);

      struct utmp* utmp_dat;
      setutent();
      utmp_dat = getutent();
      uint32_t n_users = 0;
      while((utmp_dat = getutent()) != NULL) {
        if (utmp_dat->ut_line[0] == '~') continue;
        if (utmp_dat->ut_user[0] && (strcmp(utmp_dat->ut_user, "LOGIN")==1)) {
          n_users++;
        }
      }

      /* we need to print something like:
          [current time] up [up for x minutes||hh:mm], [number of users logged in] user(s), load average [load averages]
      */

      printf(" %02d:%02d:%02d up  ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
      if(floor(uptime/3600) > 0) {
        printf("%.0lf:%.0lf,  ", floor(uptime/3600), floor(fmod(uptime, 60)));
      } else {
        printf("%.0lf min,  ", floor(uptime/60));
      }
      printf("%d user", n_users);
      if(n_users > 1) printf("s");
      printf(",  load average: ");
    }
  #endif

  #ifdef _WIN32
    // TODO windows
    // TODO do we emulate /dev/ttyX or just output CON ?
  #endif
	return 0;
}
