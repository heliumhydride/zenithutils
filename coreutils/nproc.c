#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>

#ifndef _WIN32 // On Unix
  #include <unistd.h>
#endif
#ifdef _WIN32
  #include <sysinfoapi.h>
#endif

//int main(int argc, char* argv[]) {
int main(void) {
  #ifdef _WIN32
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    unsigned int nproc = info.dwNumberOfProcessors;
  #endif

  // As always, coding for *nix is always easier than for MS/Windows 
  #ifndef _WIN32
    unsigned int nproc = sysconf(_SC_NPROCESSORS_ONLN);
  #endif

  printf("%u\n", nproc);
  return 0;
}
