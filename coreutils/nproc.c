#include <stdio.h> // printf()

#ifdef _WIN32
#include <sysinfoapi.h> // GetSystemInfo()
#else // On Unix
#include <unistd.h>     // sysconf()
#endif

int main(void)
{
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
