#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
//#include <stdlib.h>
//#include <getopt.h>
//#include <unistd.h>
//#include <string.h>

int main(int argc, char* argv[]) {
  const char* ctrl[32] = { "NUL","SOH","STX","ETX","EOT","ENQ","ACK","BEL",
                           "BS","HT","NL","VT","FF","CR","SO","SI",
                           "DLE","DC1","DC2","DC3","DC4","NAK","SYN","ETB",
                           "CAN","EM","SUB","ESC","FS","GS","RS","US"
  };

  if(argc <= 1) { // We have no argument, show the whole table
    char last[2];
    last[1] = '\0';
  
    printf("Dec Hex Oct Char | Dec Hex Oct Char | Dec Hex Oct Char | Dec Hex Oct Char\n");
    for(int i = 0; i < 32; i++) {
      printf("%3u %3x %3o %-4s | %3u %3x %3o %4c | %3u %3x %3o %4c | %3u %3x %3o %4s\n",
              i, i, i, ctrl[i],
              i+32, i+32, i+32, i+32,
              i+64, i+64, i+64, i+64,
              i+96, i+96, i+96, (i+96 == 0x7f ? "DEL" : (last[0] = i+96, last))
      );
    }
  } else {
    printf("Dec Hex Oct Char\n");
    for(int i = 1; i < argc; i++) {
      char ch = argv[i][0];
      if(ch < 32) {
        // TODO take ctrl codes as input
        printf("%3u %3x %3o %4c", ch, ch, ch, ctrl[ch]);
      } else if(ch == 127) {
        printf("%3u %3x %3o  DEL", ch, ch, ch);
      } else {
        printf("%3u %3x %3o %4c", ch, ch, ch, ch);
      }
      printf("\n");
    }
  }
  return 0;
}
