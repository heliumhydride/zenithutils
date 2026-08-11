#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // ssize_t
#include "../include/prettyprint.h"
#include "../config.h"

int factor_primes(long n, long* factors, ssize_t cap) {
  ssize_t k = 0;

  // Factor out the 2s
  while(n%2 == 0) {
    if(k >= cap) return -1; // not enough space
    factors[k++] = 2;
    n /= 2;
  }

  // Factor out the rest of the primes
  for(long d = 3; d * d <= n; d += 2) {
    while(n%d == 0) {
      if(k >= cap) return -1;
      factors[k++] = d;
      n /= d;
    }
  }

  // Remainder is a prime (>1, because 1 is cheating)
  if(n > 1) {
    if(k >= cap) return -1;
    factors[k++] = n;
  }

  return k;
}

void print_usage(char* program) {
  fprintf(stderr, "usage: %s number\n", program);
}

int main(int argc, char* argv[]) {
  if(argc < 2 || !strcmp(argv[1], "--help")) {
    print_usage(argv[0]);
    return 1;
  }

  char* endptr;
  long n = (int)strtol(argv[1], &endptr, 10);
  if(endptr == argv[1] || n <= 0) {
    print_error("%s: '%s' is not a positive integer", argv[0], argv[1]);
    return 1;
  }

  long factors[FACTOR_MAX_PRIMES];
  ssize_t count = factor_primes(n, factors, FACTOR_MAX_PRIMES);
  if(count < 0) return 1;

  printf("%ld: ", n);
  for(ssize_t i = 0; i < count; i++)
    printf("%ld%s", factors[i], (i + 1 < count) ? " " : "\n");

  return 0;
}
