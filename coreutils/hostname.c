// Why do *hostname() need this garbage? Can't there just be a '#define _POSIX to handle that?'
#define _DEFAULT_SOURCE          // sethostname()
#define _XOPEN_SOURCE   500      // gethostname()
#define _POSIX_C_SOURCE 200112L  // gethostname()

#include <stdio.h>            // puts(), fprintf()
#include <string.h>           // strlen(), strcmp()
#include "../include/util.h"  // perror2()

#ifdef _WIN32
#include <windows.h> // GetComputerName(), SetComputerName()
#else // On Unix
#include <unistd.h>  // gethostname(), sethostname()
#endif // _WIN32

#ifdef _WIN32
#undef  gethostname
int gethostname2(char* buf, size_t size)
{
    return !GetComputerName(buf, (LPDWORD)&size);
}
#define sethostname(name,size) SetComputerName((name))

#else // On Unix
#define gethostname2 gethostname
#endif // _WIN32

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s [new hostname]\n", program);
}

int main(int argc, char* argv[])
{
    if(argc < 2) { // no args, print hostname
        char hostname[512];
        if(gethostname2(hostname, sizeof(hostname)) != 0) {
            perror2("getting hostname failed", argv[0]);
            return 1;
        }
        puts(hostname);
        return 0;
    }
    
    // we have args, check if it's help
    if(!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
        print_usage(argv[0]);
        return 1;
    }

    // if not it's probably a hostname to be set
    if(sethostname(argv[1], strlen(argv[1])) == -1) {
        perror2("setting hostname failed", argv[0]);
        return 1;
    }

    return 0;
}
