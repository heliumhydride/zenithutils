#include <stdio.h>            // puts(), fprintf()
#include <stdlib.h>           // getenv()
#include <string.h>           // strcmp()
#include <unistd.h>           // getlogin()
#include "../include/util.h"  // print_error(), shift_args()

void print_usage(const char* program) {
    fprintf(stderr, "usage: %s", program);
}

int main(int argc, char* argv[])
{
    const char *program = argv[0];
    shift_args(&argc, &argv);

    if(argc <= 0 && !strcmp(*argv, "--help")) {
        print_usage(program);
        return 0;
    }

    char *username = NULL;
    #ifdef _WIN32
    // that's right we're gonna cheat (using the environment variable USERNAME)
    // TODO do this the right way?
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
