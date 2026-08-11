include ../config.mk

PROGS=ascii clear exedump read rng strings time usleep wpath zenithutils_version

all: $(PROGS)

%.o: %.c ../config.h
	$(CC) $(CFLAGS) -c $< -o $@

ascii: ascii.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

clear: clear.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

exedump: exedump.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

read: read.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

rng: rng.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@ -lsodium

strings: strings.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

time: time.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

usleep: usleep.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

wpath: wpath.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

zenithutils_version: zenithutils_version.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@
