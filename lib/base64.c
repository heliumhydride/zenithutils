#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include "../include/base64.h"

char get_base64_ch(size_t index_ch) {
  if(index_ch >= 0 && index_ch <= 25) { // A-Z
    return index_ch+65;
  } else if(index_ch >= 26 && index_ch <= 51) { // a-z
    return index_ch-26+97;
  } else if(index_ch >= 52 && index_ch <= 61) { // 0-9
    return index_ch-52+48;
  } else if(index_ch == 62) { // +
    return '+';
  } else if(index_ch == 63) { // /
    return '/';
  } else { // None of the above
    return -1;
  }
}

char* base64_encode(char* str) {
  return "not implemented"; // TODO
}

char* base64_decode(char* str) {
  return "not implemented"; // TODO
}
