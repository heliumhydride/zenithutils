#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include "../include/prettyprint.h"

void print_usage(char* program) {
  fprintf(stderr, "usage: %s [file] [file2] ...\n", program);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];
  char convert_to = 'u'; // default, u=dos2unix, d=unix2dos

  // if called as unix2dos, switch to unix2dos mode
  if(
    !strcmp(basename(program), "unix2dos") ||
    !strcmp(basename(program), "z_unix2dos") ||
    !strcmp(basename(program), "unix2dos.exe") ||
    !strcmp(basename(program), "z_unix2dos.exe")
  ) convert_to = 'd';

  if(argc == 1) {
    argv--;
    argv[1] = "-";
  }

  FILE* fp_in = stdin;
  FILE* fp_out = stdout;
  while(*++argv) {
    if(strcmp(*argv,"-"))
      fp_in = fopen(*argv, "r+");

    if(fp_in == NULL) {
      print_error("%s: %s: file not found\n", program, *argv);
      return 1;
    }

    if(fp_in != stdin) {
      if(convert_to == 'u') {
        fprintf(stderr, "%s: converting %s to Unix format...\n", program, *argv);
      } else {
        fprintf(stderr, "%s: converting %s to DOS format...\n", program, *argv);
      }
    }

    if(fp_in == stdin)
      fp_out = stdout;
    else
      fp_out = tmpfile();

    int c;
    while((c = fgetc(fp_in)) != EOF) {
      if(convert_to == 'u') {
        if(c != '\r')
          fputc(c, fp_out);
      } else {
        if(c == '\n')
          fprintf(fp_out, "\r\n");
        else
          fputc(c, fp_out);
      }
    }

    if(strcmp(*argv,"-")) {
      rewind(fp_out);
      fclose(fp_in);
      FILE* final_fp_out = fopen(*argv, "wb");
      if(final_fp_out == NULL) {
        print_error("%s: %s: failed to open file for writing", program, *argv);
        return 1;
      }

      while((c = fgetc(fp_out)) != EOF)
        fputc(c, final_fp_out);

      fclose(fp_out);
      fclose(final_fp_out);
    }
  }

  return 0;
}
