#include <stdio.h>

int main(int argc, char* argv[])
{
    char* expletive = "y";

    if(argc >= 2) expletive = argv[1];

    while(1) printf("%s\n", expletive);

    /*
        We don't need return in practice, but in theory it is needed in the eyes of the compiler, because main() should return an integer.
        Let's return a very bad integer because we're not supposed to reach this place.
    */
    return 255;
}
