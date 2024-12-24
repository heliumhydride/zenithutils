#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>

static int _b64_err = 0;
char* base64_encode(char* str);
char* base64_decode(char* str);
char get_base64_ch(size_t index_ch);

#endif
