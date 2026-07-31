#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <signal.h>
#include "../include/prettyprint.h"
#include "../include/util.h"
#include "../include/sigmap.h"
#include "../config.h"
#ifdef __linux__
#include <dirent.h>
#else
#include <sys/sysctl.h>
#include <sys/types.h>
#include <sys/user.h>
#include <pwd.h>
#endif // __linux__

int parse_sigopt(const char* s) {
  if(s == NULL || s[0] != '-')
    return -1;
  for(size_t i = 0; i < sizeof(sigmap)/sizeof(sigmap[0]); i++) {
    if(!strcmp(s, sigmap[i].opt))
      return sigmap[i].sig;
  }
  return -1;
}

#ifdef __linux__
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
#endif

#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__APPLE__)
// Should work on FreeBSD, remains to be tested on OpenBSD, NetBSD and MacOS
// Theoretically all use sysctl, however the implementation could differ
// TODO test on other *BSD systems
pid_t getpid_ext(const char* comm) {
  pid_t pid = 0;
  struct kinfo_proc* proc_list = NULL;
  size_t length = 0;
  static const int name[] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
  if(sysctl((int*)name, (sizeof(name)/sizeof(*name)) - 1, NULL, &length, NULL, 0))
    return 0;

  proc_list = malloc(length);
  if(proc_list == NULL)
    return 0;

  if(sysctl((int*)name, (sizeof(name)/sizeof(*name)) - 1, proc_list, &length, NULL, 0)) {
    free(proc_list);
    return 0;
  }

  int proc_count = length / KINFO_PROC_SIZE;
  for(int i = 0; i < proc_count; i++) {
    if(!strcmp(comm, proc_list[i].ki_comm))
      pid = proc_list[i].ki_pid;
  }

  free(proc_list);
  return pid;
}

#endif

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
          print_error("%s: cannot kill pid 0", program);
          return 1;
        }
        pid = getpid_ext(*argv);
        if(!pid) {
          print_error("%s: '%s': no such process", program, *argv);
          return 1;
        }
      }

      if(kill(pid, sig) == -1) {
        print_error("%s: killing process of PID %d failed", program, pid);
        return 1;
      }
    }
  }

  return 0;
}
