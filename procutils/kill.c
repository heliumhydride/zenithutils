#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <getopt.h>
#include <signal.h>
#include "../include/prettyprint.h"
#include "../include/util.h"
#include "../config.h"

typedef struct {
  const char *opt;
  int sig;
} sigmap_t;

const sigmap_t sigmap[] = {
  {"-SIGHUP",   SIGHUP},   {"-HUP",   SIGHUP},   {"-1",  SIGHUP},
  {"-SIGINT",   SIGINT},   {"-INT",   SIGINT},   {"-2",  SIGINT},
  {"-SIGQUIT",  SIGQUIT},  {"-QUIT",  SIGQUIT},  {"-3",  SIGQUIT},
  {"-SIGILL",   SIGILL},   {"-ILL",   SIGILL},   {"-4",  SIGILL},
  {"-SIGTRAP",  SIGTRAP},  {"-TRAP",  SIGTRAP},  {"-5",  SIGTRAP},
  {"-SIGABRT",  SIGABRT},  {"-ABRT",  SIGABRT},  {"-6",  SIGABRT},
  {"-SIGBUS",   SIGBUS},   {"-BUS",   SIGBUS},   {"-7",  SIGBUS},
  {"-SIGFPE",   SIGFPE},   {"-FPE",   SIGFPE},   {"-8",  SIGFPE},
  {"-SIGKILL",  SIGKILL},  {"-KILL",  SIGKILL},  {"-9",  SIGKILL},
  {"-SIGUSR1",  SIGUSR1},  {"-USR1",  SIGUSR1},  {"-10", SIGUSR1},
  {"-SIGSEGV",  SIGSEGV},  {"-SEGV",  SIGSEGV},  {"-11", SIGSEGV},
  {"-SIGUSR2",  SIGUSR2},  {"-USR2",  SIGUSR2},  {"-12", SIGUSR2},
  {"-SIGPIPE",  SIGPIPE},  {"-PIPE",  SIGPIPE},  {"-13", SIGPIPE},
  {"-SIGALRM",  SIGALRM},  {"-ALRM",  SIGALRM},  {"-14", SIGALRM},
  {"-SIGTERM",  SIGTERM},  {"-TERM",  SIGTERM},  {"-15", SIGTERM},
  {"-SIGCHLD",  SIGCHLD},  {"-CHLD",  SIGCHLD},  {"-17", SIGCHLD},
  {"-SIGCONT",  SIGCONT},  {"-CONT",  SIGCONT},  {"-18", SIGCONT},
  {"-SIGSTOP",  SIGSTOP},  {"-STOP",  SIGSTOP},  {"-19", SIGSTOP},
  {"-SIGTSTP",  SIGTSTP},  {"-TSTP",  SIGTSTP},  {"-20", SIGTSTP},
  {"-SIGTTIN",  SIGTTIN},  {"-TTIN",  SIGTTIN},  {"-21", SIGTTIN},
  {"-SIGTTOU",  SIGTTOU},  {"-TTOU",  SIGTTOU},  {"-22", SIGTTOU},
  {"-SIGURG",   SIGURG},   {"-URG",   SIGURG},   {"-23", SIGURG},
  {"-SIGXCPU",  SIGXCPU},  {"-XCPU",  SIGXCPU},  {"-24", SIGXCPU},
  {"-SIGXFSZ",  SIGXFSZ},  {"-XFSZ",  SIGXFSZ},  {"-25", SIGXFSZ},
  {"-SIGPROF",  SIGPROF},  {"-PROF",  SIGPROF},  {"-27", SIGPROF},
  {"-SIGWINCH", SIGWINCH}, {"-WINCH", SIGWINCH}, {"-28", SIGWINCH},
  {"-SIGIO",    SIGIO},    {"-IO",    SIGIO},    {"-29", SIGIO},
  {"-SIGSYS",   SIGSYS},   {"-SYS",   SIGSYS},   {"-31", SIGSYS}
};

int parse_sigopt(const char* s) {
  if(s == NULL || s[0] != '-')
    return -1;
  for(size_t i = 0; i < sizeof(sigmap)/sizeof(sigmap[0]); i++) {
    if(!strcmp(s, sigmap[i].opt))
      return sigmap[i].sig;
  }
  return -1;
}

pid_t getpid_ext(const char* comm) {
  pid_t pid = 0;
  DIR* d = opendir("/proc");
  if(d == NULL)
    return 0;

  struct dirent* ent;
  while((ent = readdir(d))) {
    if(str_is_nan(ent->d_name)) continue;
    pid = atoi(ent->d_name);
    
    char path[PATHNAME_MAX];
    snprintf(path, sizeof(path), "/proc/%d/comm", pid);
    FILE* fp = fopen(path, "r");
    if(fp == NULL)
      continue;

    char comm2[PATHNAME_MAX];
    if(fgets(comm2, sizeof(comm2), fp)) {
      comm2[strcspn(comm2, "\n")] = 0; // trim newline
      if (strcmp(comm2, comm) == 0) {
        fclose(fp);
        closedir(d);
        return pid;
      }
    }
    fclose(fp);
  }
  closedir(d);
  return 0;
}

void print_usage(char* program) {
  fprintf(stderr, "usage: %s [-signal] pid|name [pid2|name2] ...\n", program);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];
  if(argc <= 1) {
    print_usage(program);
    return 1;
  }

  int sig = SIGTERM;
  for(int i = 1; i < argc; i++) {
    int s = parse_sigopt(argv[i]);
    if(s != -1) {
      sig = s;
      break;
    }
  }

  while(*++argv) {
    if(parse_sigopt(*argv) == -1) {
      pid_t pid = (int)atoi(*argv);

      if(pid == 0) {
        if(!strcmp(*argv, "0")) {
          print_error("%s: cannot kill pid 0\n", program);
          return 1;
        }
        pid = getpid_ext(*argv);
        if(!pid) {
          print_error("%s: '%s': no such process\n", program, *argv);
          return 1;
        }
      }

      if(kill(pid, sig) == -1) {
        print_error("%s: killing process of PID %s failed\n", program, *argv);
        return 1;
      }
    }
  }


  return 0;
}
