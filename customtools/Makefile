include ../config.mk

PROGS=ascii clear exedump read rng strings time usleep zenithutils_version

all: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

ascii: ascii.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

clear: clear.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

exedump: exedump.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@ -lm

read: read.o ../lib/prettyprint.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

rng: rng.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@ -lsodium

strings: strings.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

time: time.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

usleep: usleep.o ../lib/prettyprint.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@

zenithutils_version: zenithutils_version.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$@
