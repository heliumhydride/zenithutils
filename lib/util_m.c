#define _POSIX_C_SOURCE 200112L

#include "../include/util_m.h"

void format_time(int* new_time, float time) {
  new_time[0] = (int)floor(time/3600);             // hours
  new_time[1] = (int)floor(fmod(time, 3600) / 60); // minutes
  new_time[2] = (int)floor(fmod(time, 60));        // seconds
}
