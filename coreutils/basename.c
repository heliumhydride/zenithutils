#include <stdio.h>  // fprintf(), puts()
#include <libgen.h> // basename()
#include <string.h> // strlen(), strcmp()

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s string [suffix]\n", program);
}

int main(int argc, char* argv[])
{
    if(argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    char* p = basename(argv[1]);
    if(p == NULL) return 1;

    size_t off;
    if(argc >= 3) {
        off = strlen(p) - strlen(argv[2]);
        if(off > 0 && !strcmp(p + off, argv[2]))
            p[off] = '\0';
    }

    puts(p);
    return 0;
}
