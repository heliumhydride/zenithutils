// ZU = ZenithUtils
#ifndef ZU_COLORS_H
#define ZU_COLORS_H

// TODO considering to rename this ansi.h, also maybe don't rely on it too much for programs not supporting it, maybe an create ifdef ANSI_SUPPORT and a configure switch --disable-ansi-support

#define ANSI_NORM    "\033[0m"
#define ANSI_BOLD    "\033[1m"
#define ANSI_FAINT   "\033[2m"
#define ANSI_ITALIC  "\033[3m"
#define ANSI_UNDER   "\033[4m"
#define ANSI_BLINK   "\033[5m"
#define ANSI_INVERT  "\033[7m"
#define ANSI_STRIKE  "\033[9m"

#define ANSI_RED     "\033[1;31m"
#define ANSI_GREEN   "\033[1;32m"
#define ANSI_YELLOW  "\033[1;33m"
#define ANSI_BLUE    "\033[1;34m"
#define ANSI_MAGENTA "\033[1;35m"
#define ANSI_CYAN    "\033[1;36m"

#endif // ZU_COLORS_H
