#include <stdio.h>            // printf(), putchar(), fprintf()
#include <stdint.h>           // int8_t
#include <stdlib.h>           // strtol()
#include <string.h>           // strcmp()
#include "../include/util.h"  // shift_args(), print_error(), str_startwith()
#include "../config.h"        // ASCII_SHOW_OCTAL

typedef struct {
    const char*   representation;
    const int8_t  code;
} asciientry_t;

asciientry_t ascii_map[] = {
    {"NUL", 0x0},  {"SOH", 0x1},  {"STX", 0x2},  {"ETX", 0x3},  {"EOT", 0x4},  {"ENQ", 0x5},  {"ACK", 0x6},  {"BEL", 0x7},
    {"BS", 0x8},   {"HT", 0x9},   {"NL", 0xa},   {"VT", 0xb},   {"FF", 0xc},   {"CR", 0xd},   {"SO", 0xe},   {"SI", 0xf},
    {"DLE", 0x10}, {"DC1", 0x11}, {"DC2", 0x12}, {"DC3", 0x13}, {"DC4", 0x14}, {"NAK", 0x15}, {"SYN", 0x16}, {"ETB", 0x17},
    {"CAN", 0x18}, {"EM", 0x19},  {"SUB", 0x1a}, {"ESC", 0x1b}, {"FS", 0x1c},  {"GS", 0x1d},  {"RS", 0x1e},  {"US", 0x1f},
    {" ", 0x20},   {"!", 0x21},   {"\"", 0x22},  {"#", 0x23},   {"$", 0x24},   {"%", 0x25},   {"&", 0x26},   {"'", 0x27},
    {"(", 0x28},   {")", 0x29},   {"*", 0x2a},   {"+", 0x2b},   {",", 0x2c},   {"-", 0x2d},   {".", 0x2e},   {"/", 0x2f},
    {"0", 0x30},   {"1", 0x31},   {"2", 0x32},   {"3", 0x33},   {"4", 0x34},   {"5", 0x35},   {"6", 0x36},   {"7", 0x37},
    {"8", 0x38},   {"9", 0x39},   {":", 0x3a},   {";", 0x3b},   {"<", 0x3c},   {"=", 0x3d},   {">", 0x3e},   {"?", 0x3f},
    {"@", 0x40},   {"A", 0x41},   {"B", 0x42},   {"C", 0x43},   {"D", 0x44},   {"E", 0x45},   {"F", 0x46},   {"G", 0x47},
    {"H", 0x48},   {"I", 0x49},   {"J", 0x4a},   {"K", 0x4b},   {"L", 0x4c},   {"M", 0x4d},   {"N", 0x4e},   {"O", 0x4f},
    {"P", 0x50},   {"Q", 0x51},   {"R", 0x52},   {"S", 0x53},   {"T", 0x54},   {"U", 0x55},   {"V", 0x56},   {"W", 0x57},
    {"X", 0x58},   {"Y", 0x59},   {"Z", 0x5a},   {"[", 0x5b},   {"\\", 0x5c},  {"]", 0x5d},   {"^", 0x5e},   {"_", 0x5f},
    {"`", 0x60},   {"a", 0x61},   {"b", 0x62},   {"c", 0x63},   {"d", 0x64},   {"e", 0x65},   {"f", 0x66},   {"g", 0x67},
    {"h", 0x68},   {"i", 0x69},   {"j", 0x6a},   {"k", 0x6b},   {"l", 0x6c},   {"m", 0x6d},   {"n", 0x6e},   {"o", 0x6f},
    {"p", 0x70},   {"q", 0x71},   {"r", 0x72},   {"s", 0x73},   {"t",0x74},    {"u", 0x75},   {"v", 0x76},   {"w", 0x77},
    {"x", 0x78},   {"y", 0x79},   {"z", 0x7a},   {"{", 0x7b},   {"|", 0x7c},   {"}", 0x7d},   {"~", 0x7e},   {"DEL", 0x7f}
};

void print_usage(const char *program)
{
    fprintf(stderr, "usage: %s [-l] [repr] | [code]\n", program);
}

asciientry_t* ascii_from_repr(const char *repr)
{
    for(size_t i = 0; i < 128; i++) {
        if(!strcmp(repr, ascii_map[i].representation))
            return ascii_map + i;
    }
    return NULL;
}

asciientry_t* ascii_from_code(const char c)
{
    for(size_t i = 0; i < 128; i++) {
        if((char)(ascii_map[i].code) == c)
            return ascii_map + i;
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    const char *program = argv[0];
    shift_args(&argc, &argv);
    char* fmt;
    int lflag = 0; /*  the next arguments are literal
                       e.g. 'ascii -l 1' would print ascii for the
                           literal character '1', not code 0x01     
                       exceptions are hex and octal literals
                       they are always interpreted as codes */

    if(argc >= 1) {
        if(!strcmp(*argv, "--help")) {
            print_usage(program);
            return 0;
        } else if(!strcmp(*argv, "-l")) {
            shift_args(&argc, &argv);
            lflag = 1;
        }
    }

#if ASCII_SHOW_OCTAL
    fmt = "%3d %02X %03o %-3s ";
#else
    fmt = "%3d %02X %-3s ";
#endif // ASCII_SHOW_OCTAL

    if(argc <= 0) { // no argument, show whole ascii table
#if ASCII_SHOW_OCTAL
        printf("Dec Hx Oct     Dec Hx Oct     Dec Hx Oct     Dec Hx Oct     Dec Hx Oct     Dec Hx Oct     Dec Hx Oct     Dec Hx Oct\n");
#else
        printf("Dec Hx     Dec Hx     Dec Hx     Dec Hx     Dec Hx     Dec Hx     Dec Hx     Dec Hx\n");
#endif // ASCII_SHOW_OCTAL
        for(int r = 0; r < 16; r++) {
            for(int c = 0; c < 8; c++) {
                int i = r + 16*c;
                printf(fmt,
                    ascii_map[i].code,
                    ascii_map[i].code,
#if ASCII_SHOW_OCTAL
                    ascii_map[i].code,
#endif
                    ascii_map[i].representation
                );
            }
            putchar('\n');
        }
    } else {
        printf("Dec Hx");
#if ASCII_SHOW_OCTAL
        printf(" Oct");
#endif
        putchar('\n');
        while(*argv) {
            int base = 10;
            if(str_startwith(*argv, "0x"))  { (*argv) += 2; base = 16; }
            if(str_startwith(*argv, "0o"))  { (*argv) += 2; base = 8;  }

            asciientry_t* entry = NULL;
            char *endptr = *argv;

            if(!lflag || base != 10)
                entry = ascii_from_code((char)strtol(*argv, &endptr, base));

            if(!strcmp(*argv, endptr)) {
                entry = ascii_from_repr(*argv);
                if(!entry) {
                    print_error("%s: invalid ascii representation '%s'", program, *argv);
                    return 1;
                }
            }

            printf(fmt,
                entry->code,
                entry->code,
#if ASCII_SHOW_OCTAL
                entry->code,
#endif // ASCII_SHOW_OCTAL
                entry->representation
            );
            putchar('\n');
            shift_args(&argc, &argv);
        }
    }
    return 0;
}
