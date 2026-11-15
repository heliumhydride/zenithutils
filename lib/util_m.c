#include "../include/util_m.h"

/*
    The sole reason this file exists is because I needed to split libutil in two

    The part that uses -lm (this) and the rest, because it avoid needing to link with libm everytime
    libutil is used.
*/

void format_time(int* new_time, const float time)
{
  new_time[0] = (int)floor(time/3600);             // hours
  new_time[1] = (int)floor(fmod(time, 3600) / 60); // minutes
  new_time[2] = (int)floor(fmod(time, 60));        // seconds
}
