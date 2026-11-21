#include <stdio.h> // printf()

#ifdef _WIN32
#include <windows.h> /* GetConsoleScreenBufferInfo()
                        FillConsoleOutputCharacter()
                        FillConsoleOutputAttribute()
                        SetConsoleCursorPosition(),
                        GetStdHandle() */

/*
    This function is the reason I am glad Win10+ cmd supports ansi escape clearing...

    Stolen from https://learn.microsoft.com/en-us/windows/console/clearing-the-screen
    ^^^ Well I mean it was given away for free... I just happened to use it ;)

    Code was cleaned up[1] compared to the original eyesore.

    [1] As much as Win32 code can be clean of course
*/
void cls(HANDLE hConsole)
{
    /*
        M****soft when designing the win32 api:

            " Look, we're so quirky and different!             \
            Let's make our typedefs all caps, and create        \
            unnecessary aliases for already existing types! [2]"

        There's no rational explanation for this, this is just pure malice.

        [2] DWORD, BOOL, ...
    */

    COORD coordScreen = {0,0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
        return;

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    BOOL res = FillConsoleOutputCharacter(
        hConsole,
        (TCHAR)' ',
        dwConSize,
        coordScreen,
        &cCharsWritten
    );
    if(!res) return;

    if(!GetConsoleScreenBufferInfo(hConsole, &csbi))
        return;

    res = FillConsoleOutputAttribute(
        hConsole,
        csbi.wAttributes,
        dwConSize,
        coordScreen,
        &cCharsWritten
    );

    if(!res) return;
    SetConsoleCursorPosition(hConsole, coordScreen);
    // That was an adventure... Now the screen is cleared!
}
#endif // _WIN32

int main(void)
{
    #ifdef _WIN32
    HANDLE hStdout;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    cls(hStdout);
    #else // On NORMAL REASONABLE SYSTEMS (posix)
    printf("\033[H\033[J");
    #endif // _WIN32
    return 0;
}
