#include <stdio.h>
#include <unistd.h>

int main(void)
{
    #ifdef _WIN32
    printf("CON\n"); // assume con device on windows
    #else // On Unix
    char* tty_dev = ttyname(STDIN_FILENO);
    if(tty_dev == NULL) {
        puts("not a tty");
        return 1;
    }
    puts(tty_dev);
    #endif

    return 0;
}
