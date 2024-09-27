#define _POSIX_C_SOURCE 200112L

#include <stdio.h>

int main(int argc, char* argv[]){
  char* expletive = "y";

  if(argc >= 2)
    expletive = argv[1];

  while(1)
    printf("%s\n", expletive);

  // we dont need return ?
  return 0;
}
