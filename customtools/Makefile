include ../config.mk

PROGS=ascii clear errno exedump read rng strings time usleep wpath zenithutils_version

all: $(PROGS)

$(PROGS): %: ../o/bin/$(PROG_PREFIX)%

%.o: %.c ../config.h
	@echo "  CC    $(notdir $@)"
	@$(CC) $(CFLAGS) -DPROG_PREFIX=\"$(PROG_PREFIX)\" -c $< -o $@

.SECONDEXPANSION:

../o/bin/$(PROG_PREFIX)%: %.o $$(OBJS)
	@echo "  LD    $(notdir $@)"
	@$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

../o/bin/$(PROG_PREFIX)errno: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)exedump: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)read: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)rng: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)strings: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)time: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)usleep: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)wpath: OBJS = ../lib/util.o

../o/bin/$(PROG_PREFIX)rng: LIBS = -lsodium

.PHONY: all $(PROGS)
