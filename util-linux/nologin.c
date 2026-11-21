#include <stdio.h> // fopen(), putchar(), fgetc()

int main(void)
{
    FILE* fp = fopen("/etc/nologin.txt", "r");
    if(fp == NULL) {
        printf("This account is currently not available.\n");
        return 1;
    }

    int c;
    while((c = fgetc(fp)) != EOF)
        putchar(c);

    return 1;
}
