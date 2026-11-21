#include <stdio.h> // puts()

int main(int argc, char* argv[])
{
    char* expletive = "y";
    if(argc >= 2) expletive = argv[1];
    while(1) puts(expletive);
    return 255;
}
