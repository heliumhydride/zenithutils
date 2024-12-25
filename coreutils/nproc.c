#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>

#ifdef _WIN32
  #include <sysinfoapi.h>
#else // On Unix
  #include <unistd.h>
#endif

//int main(int argc, char* argv[]) {
int main(void) {
  #ifdef _WIN32
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    unsigned int nproc = info.dwNumberOfProcessors;
  #else // On Unix
  // As always, coding for *nix is always easier than for MS/Windows 
    unsigned int nproc = sysconf(_SC_NPROCESSORS_ONLN);
  #endif

  printf("%u\n", nproc);
  return 0;
}
