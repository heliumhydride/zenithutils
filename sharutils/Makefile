include ../config.mk

PROGS=shar uuencode uudecode

all: $(PROGS)

%.o: %.c ../config.h
	$(CC) $(CFLAGS) -c $< -o $@

shar: shar.sh
	cp shar.sh ../o/bin/$(PROG_PREFIX)shar

uuencode: uuencode.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

uudecode: uudecode.o ../lib/util.o
	$(LD) $(LDFLAGS) $^ -o ../o/bin/$(PROG_PREFIX)$@

