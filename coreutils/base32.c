#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "../include/prettyprint.h"
#include "../include/util.h"

static int _b32_err = 0;

size_t base32_encoded_len(const size_t in_len) {
  return ((in_len * 8 + 4) / 5) + 7;
}

// TODO it kind of works but too much padding
size_t base32_encode(const uint8_t* data, size_t len, char* out) {
  size_t out_len = base32_encoded_len(len);
  size_t bitbuf = 0;
  int bits_left = 0;
  size_t out_i = 0;

  for(size_t i = 0; i < len; i++) {
    bitbuf = (bitbuf << 8) | data[i];
    bits_left += 8;
    while(bits_left >= 5) {
      int shift = bits_left - 5;
      uint8_t index = (bitbuf >> shift) & 31;
      out[out_i++] = BASE32_AB[index];
      bits_left -= 5;
    }
  }

  if (bits_left > 0) {
    uint8_t index = (bitbuf << (5 - bits_left)) & 31;
    out[out_i++] = BASE32_AB[index];
  }

  while (out_i < out_len) out[out_i++] = '='; // padding
  out[out_i] = '\0';
  return out_i;
}

int b32_value(char c) {
  if(c >= 'A' && c <= 'Z') return c - 'A';
  if(c >= '2' && c <= '7') return 26 + (c - '2');
  return -1;
}

size_t base32_decode(const char* in, uint8_t* out, int iflag) {
  (void)iflag;
  // ^^^ TODO work with -i

  size_t in_len = strlen(in);
  size_t chars = 0;
  for(size_t i = 0; i < in_len; i++) {
    if(in[i] == '=') break;
    if(!isspace((uint8_t)in[i])) chars++;
  }

  size_t out_i = 0;
  size_t bitbuf = 0;
  int bits_left = 0;

  for(size_t i = 0; i < in_len; i++) {
    char c = in[i];
    if (c == '=') break;
    if (isspace((uint8_t)c)) continue;

    int v = b32_value(c);
    if(v < 0) {
      return 0;
      _b32_err = 1;
    }

    bitbuf = (bitbuf << 5) | (uint32_t)v;
    bits_left += 5;

    if(bits_left >= 8) {
      bits_left -= 8;
      uint8_t byte = (uint8_t)((bitbuf >> bits_left) & 0xFF);
      out[out_i++] = byte;
    }
  }
  return out_i;
}

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-di] [file]\n", argv0);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];
  int dflag = 0; // decode mode
  int iflag = 0; // ignore garbage TODO make use of -i

  int opt;
  while((opt = getopt(argc, argv, ":di")) != -1) {
    switch(opt) {
      case 'd':
        dflag = 1;
        break;
      case 'i':
        iflag = 1;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", program, optopt);
        print_usage(program);
        return 1;
        break;
    }
  }

  argc -= optind;
  argv += optind;

  FILE* fp = stdin;
  if(argc > 0) {
    if(strcmp(*argv, "-")) {
      fp = fopen(*argv, "rb");
      if(fp == NULL) {
        print_error("%s: %s: could not open file", program, *argv);
        return 1;
      }
    }
  }

  uint8_t* input;
  if(fp == stdin)
    input = malloc(STDIN_MAX);
  else
    input = malloc(get_filesize(fp));

  size_t i = 0;
  int c;
  while((c = fgetc(fp)) != EOF) {
    input[i] = (uint8_t)c;
    i++;
  }
  if(fp != stdin)
    fclose(fp);

  size_t written;
  char* result;
  if(dflag) {
    result = malloc(i); // more than enough
    written = base32_decode((char*)input, (uint8_t*)result, iflag);
  } else {
    result = malloc(base32_encoded_len(i));
    written = base32_encode(input, i, result);
  }

  if(NULL == result || _b32_err > 0 || written == 0) { // TODO better err handling
    print_error("%s: base32 encoding/decoding failed", program);
    return 1;
  }

  puts(result);
  free(result);
  return 0;
}
