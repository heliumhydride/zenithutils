#include <stdio.h>

int main(void)
{
    // TODO windows(mingw) uses win32 api to clear console (not all cmds support vt100 escapes)
    printf("\033[H\033[J");
    return 0;
}
