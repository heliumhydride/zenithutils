#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
#include "windows.h"
#endif

#include "../include/prettyprint.h"

/*
void print_usage(const char* program) {
    fprintf(stderr, "usage: %s", program);
}
*/

int main(int argc, char* argv[])
{
    char* username = NULL;

    #ifdef _WIN32
    // that's right we're gonna cheat (using the environment variable USERNAME)
    username = getenv("USERNAME");
    #else // On Unix
    // TODO when i run "su root" and then run o/usr/bin/whoami, it shows my username before running su instead of "root"... [probably because this acts like logname and not whoami]
    username = getlogin();
    #endif

    if(username == NULL) {
        print_error("%s: getting username failed", argv[0]);
        return 1;
    }
    puts(username);
    return 0;
}
