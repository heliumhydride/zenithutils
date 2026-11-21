#include <stdio.h>  // puts()
#include <unistd.h> // ttyname()

int main(void)
{
    #ifdef _WIN32
    puts("CON"); // assume con device on windows
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
