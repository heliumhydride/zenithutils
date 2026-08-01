# Prepend every program filename with $(PROG_PREFIX), e.g z_readlink
# needed for programs who require to know their program names (eg: unix2dos)
PROG_PREFIX=
#PROG_PREFIX=z_

CC = cc
LD = $(CC)

CFLAGS = -O2 -std=c99 -Wall -Wextra -Wpedantic
LDFLAGS = $(CFLAGS)
WIN32 = 0
# WINNT_ALIAS_CFLAGS = -Os -nostdlib -lkernel32 -lntdll -lmingw32

