#ifndef ZU_CONFIG_H
#define ZU_CONFIG_H

#define VERSION "v0.01a"

/*
  global options
*/

// recommended values are either 4096 or 65535 (default 4096)
#define STDIN_MAX 4096 // Maximum buffer for stdin input

/*
  coreutils options
*/

// Explanation:
//   by default, seq only strictly allows printf formats that have a directive, eg "hello(%g)"
//   if STRICT_SEQ is disabled, it would allow multiple printing using seq:
//     $ seq -f "hello" -s " " 1 2
//     hello hello
//   however, this is NON STANDARD behaviour and therefore STRICT_SEQ is on by default
// Comment to disable
#define STRICT_SEQ 1

// If 1, print 'c:/path/to/dir' instead of 'c:\path\to\dir' (default 1)
#define FORCE_MINGW_PATHS 1
#define MAX_LINK_LENGTH 1024 // for readlink

/*
  Base32 and Base64 alphabets
*/

#define base32ab "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"
#define base64ab "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

/*
  exedump output colors (uses ANSI escape color codes)
*/

#define exedump_col1 "\033[1;34m"
#define exedump_col2 "\033[1;31m"

#endif
