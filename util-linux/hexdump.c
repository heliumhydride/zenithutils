#include <stdio.h>            // fprintf(), printf(), putchar(), fopen(), fclose()
#include <stdint.h>           // uint8_t
#include <string.h>           // strlen(), memset()
#include <ctype.h>            // isprint()
#include "../include/util.h"  // print_error(), shift_args()

void print_ascii_representation(const uint8_t* buf)
{
    printf(" |");
    for(size_t i = 0; i < 0x10; i++) {
        if(buf[i] == '\0') break;
        putchar(isprint(buf[i]) ? buf[i] : '.');
    }
    putchar('|');
}

void print_usage(const char* program)
{
    fprintf(stderr, "usage: %s file\n", program);
}

// TODO options
int main(int argc, char* argv[])
{
    const char* program = argv[0];
    shift_args(&argc, &argv)

    if(argc <= 0) {
        print_usage(program);
        return 1;
    }

    FILE* fp = fopen(*argv, "rb");
    if(fp == NULL) {
        print_error("%s: %s: could not open file", program, *argv);
        return 1;
    }

    uint8_t buf[0x10] = {0};
    size_t addr = 0x00;
    int c;
    while((c = fgetc(fp)) != EOF) {
        if((addr % 0x10) == 0) printf("%08zx  ", addr);
        if((addr % 0x10) == 0x08) putchar(' ');

        printf("%02x ", (uint8_t)c);
        if(c == '\0') buf[addr % 0x10] = '.'; // [1]
        else          buf[addr % 0x10] = (uint8_t)c;
        // [1] secret magic trick, avoids cutting the buffer because we check using '\0'. we can do that because NUL would display as '.' anyway

        if((++addr % 0x10) == 0) {
            print_ascii_representation(buf);
            putchar('\n');
            memset(buf, 0, 0x10);
        }
    }

    if((addr % 0x10) > 0) {
        // TODO incorrect amount of spaces sometimes
        int spaces = 16*3 - (int)(strlen((char*)buf)*3);
        printf("%*s", spaces, " ");
        print_ascii_representation(buf);
        putchar('\n');
    }
    printf("%08zx\n", addr);

    fclose(fp);
    return 0;
}

