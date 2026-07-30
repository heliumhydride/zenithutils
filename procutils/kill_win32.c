#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/prettyprint.h"
#include "../include/util.h"

#include <windows.h>
#include <tlhelp32.h>

int getpid_ext(const char* image) {
  int pid = 0;
  HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if(hSnap == INVALID_HANDLE_VALUE)
    return 0;

  PROCESSENTRY32 pe32;
  pe32.dwSize = sizeof(PROCESSENTRY32);

  if(Process32First(hSnap, &pe32)) {
    while(Process32Next(hSnap, &pe32)) {
      if (strcmp(pe32.szExeFile, image) == 0)
        pid = pe32.th32ProcessID;
    }
  }

  CloseHandle(hSnap);
  return pid;
}

void print_usage(char* program) {
  fprintf(stderr, "usage: %s pid|name [pid2|name2]", program);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];

  if(argc <= 1) {
    print_usage(program);
    return 1;
  }

  while(*++argv) {
    int pid = (int)atoi(*argv);

    if(pid == 0) {
      if(!strcmp(*argv, "0")) {
        print_error("%s: cannot kill pid 0\n", program);
        return 1;
      }

      // we have a name, not a pid because arg is not a number
      // so get pid
      char* image = *argv;
      pid = getpid_ext(image);
      if(!pid) { // try again but with .exe
        strcat(image, ".exe");
        pid = getpid_ext(image);
      }

      if(!pid) {
        print_error("%s: '%s': no such process\n", program, *argv);
        return 1;
      }
    }

    HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if(hProc == NULL) {
      print_error("%s: unable to get handle for process of pid %d\n", program, pid);
      return 1;
    }

    if(!TerminateProcess(hProc, 1)) {
      print_error("%s: unable to terminate process of pid %d\n", program, pid);
      return 1;
    }

    CloseHandle(hProc);
  }
  return 0;
}
