CC = cc
LD = $(CC)

CFLAGS = -O2 -std=c99 -Wall -Wextra -Wpedantic
LDFLAGS = $(CFLAGS)
WIN32 = 0
# WINNT_ALIAS_CFLAGS = -Os -nostdlib -lkernel32 -lntdll -lmingw32
