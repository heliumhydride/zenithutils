#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
//#include <getopt.h>
#include <unistd.h>
//#include <string.h>

#ifdef _WIN32
#include "windows.h"
#endif

#include "../include/prettyprint.h"

/*
void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s", argv0);
}
*/

int main(int argc, char* argv[]){
  char* username;
  #ifndef _WIN32 // On Unix
  // i am always irrationally scared of malloc/free
  username = malloc(255);
  getlogin_r(username, sizeof(username));
  #endif

  #ifdef _WIN32
  // that's right we're gonna cheat (using the environment variable USERNAME)
  username = getenv("USER");
  if(username != NULL) {
    print_error("%s: getting username from environment failed");
    return 1;
  }
  #endif

  printf("%s\n", username);
  free(username);
	return 0;
}
