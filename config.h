#ifndef ZU_CONFIG_H
#define ZU_CONFIG_H

#define VERSION "v0.01a"

/*
  coreutils options
*/

// If 1, print 'c:/path/to/dir' instead of 'c:\path\to\dir'
#define FORCE_MINGW_PATHS 1

/*
  Base32 and Base64 alphabets
*/

static const char* base32ab = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
static const char* base64ab = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/*
  exedump output colors (uses ANSI escape color codes)
*/

static char* exedump_col1 = "\033[1;34m";
static char* exedump_col2 = "\033[1;31m";

#endif
